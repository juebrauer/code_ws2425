import logging

import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.utils.data import DataLoader, Dataset
import torchinfo


# Logger konfigurieren
logging.basicConfig(
    filemode="w",
    filename='logfile.txt',
    level=logging.INFO, # Log-Level: DEBUG, INFO, WARNING, ERROR, CRITICAL
    #format='%(asctime)s - %(levelname)s - %(message)s'  # Log-Format
    format='%(message)s'  # Log-Format
)

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
logging.info(f"Device: {device}")


class SimpleAttention(nn.Module):
    """
    A simple single-head attention module.
    """
    def __init__(self, embed_size):
        super(SimpleAttention, self).__init__()
        self.embed_size = embed_size

        # Linear layers for query, key, and value
        self.query = nn.Linear(embed_size, embed_size)
        self.key = nn.Linear(embed_size, embed_size)
        self.value = nn.Linear(embed_size, embed_size)

    def forward(self, queries, keys, values, mask=None):
        # Compute scores
        scores = torch.matmul(self.query(queries), self.key(keys).transpose(-2, -1))
        scores /= self.embed_size ** 0.5

        if mask is not None:
            scores = scores.masked_fill(mask == 0, float("-inf"))

        # Softmax over the scores to get attention weights
        attention_weights = F.softmax(scores, dim=-1)

        # Multiply attention weights by values
        output = torch.matmul(attention_weights, self.value(values))
        return output


class SingleEncoderLayer(nn.Module):
    """
    A single encoder block of the Transformer model.
    """
    def __init__(self, embed_size):
        super(SingleEncoderLayer, self).__init__()
        self.attention = SimpleAttention(embed_size)
        self.norm1 = nn.LayerNorm(embed_size)
        self.norm2 = nn.LayerNorm(embed_size)
        self.feed_forward = nn.Sequential(
            nn.Linear(embed_size, embed_size * 4),
            nn.ReLU(),
            nn.Linear(embed_size * 4, embed_size)
        )

    def forward(self, x):

        # Apply attention and add skip connection
        attention = self.attention(x, x, x)
        x = self.norm1(attention + x)

        # Apply feed-forward network and add skip connection
        forward = self.feed_forward(x)
        out = self.norm2(forward + x)
        return out


class SingleDecoderLayer(nn.Module):
    """
    A single decoder layer of the Transformer model.
    """

    def __init__(self, embed_size):
        super(SingleDecoderLayer, self).__init__()
        self.self_attention = SimpleAttention(embed_size)
        self.norm1 = nn.LayerNorm(embed_size)
        self.encoder_attention = SimpleAttention(embed_size)
        self.norm2 = nn.LayerNorm(embed_size)
        self.norm3 = nn.LayerNorm(embed_size)
        self.feed_forward = nn.Sequential(
            nn.Linear(embed_size, embed_size * 4),
            nn.ReLU(),
            nn.Linear(embed_size * 4, embed_size)
        )

    def forward(self, x, encoder_output):

        # Dynamic generation of target mask based on sequence length
        seq_length = x.size(1)
        trg_mask = torch.tril(torch.ones(seq_length, seq_length, device=x.device)).bool()

        # Self-attention
        self_attention = self.self_attention(x, x, x, trg_mask)
        x = self.norm1(self_attention + x)

        # Encoder-decoder attention
        encoder_attention = self.encoder_attention(x, encoder_output, encoder_output, None)
        x = self.norm2(encoder_attention + x)

        # Feed-forward network
        forward = self.feed_forward(x)
        out = self.norm3(forward + x)
        return out




class SimpleTransformer(nn.Module):
    """
    The complete Transformer model.
    """

    def __init__(self, embed_size, src_vocab_size, trg_vocab_size, num_layers, max_length):
        super(SimpleTransformer, self).__init__()
        self.embed_size = embed_size
        self.src_embedding = nn.Embedding(src_vocab_size, embed_size)
        self.trg_embedding = nn.Embedding(trg_vocab_size, embed_size)
        self.position_embedding = nn.Embedding(max_length, embed_size)
        self.encoder = nn.ModuleList([SingleEncoderLayer(embed_size) for _ in range(num_layers)])
        self.decoder = nn.ModuleList([SingleDecoderLayer(embed_size) for _ in range(num_layers)])
        self.fc_out = nn.Linear(embed_size, trg_vocab_size)
                

    def forward(self, src, trg):
        # Embedding with positional encoding
        src_positions = torch.arange(0, src.size(1)).unsqueeze(0).to(src.device)
        trg_positions = torch.arange(0, trg.size(1)).unsqueeze(0).to(trg.device)
        src = self.src_embedding(src) + self.position_embedding(src_positions)
        trg = self.trg_embedding(trg) + self.position_embedding(trg_positions)

        # Encoder
        for layer in self.encoder:
            src = layer(src)

        # Decoder
        for layer in self.decoder:
            trg = layer(trg, src)

        # Output layer
        out = self.fc_out(trg)
        return out


def tokenize(text : str) -> str:
    """
    Tokenize a text into words with lower case letters.
    """
    text = text.replace(".", " ")
    text = text.replace(",", " ")
    return text.lower().split()


def build_vocab(texts):
    vocab = {"<unk>": 0, "<pad>": 1, "<sos>": 2, "<eos>": 3}
    for text in texts:
        for token in tokenize(text):
            if token not in vocab:
                vocab[token] = len(vocab)
    return vocab


class TextDataset(Dataset):
    def __init__(self, texts, vocab, seq_length):
        self.texts = texts
        self.vocab = vocab
        self.seq_length = seq_length
        self.data = []

        for text in texts:
            tokens = ["<sos>"] + tokenize(text) + ["<eos>"]
            token_ids = [vocab.get(token, vocab["<unk>"]) for token in tokens]

            # Erzeuge Trainingsdaten mit Padding auf die maximale Länge
            for start_idx in range(len(token_ids)):
                src = token_ids[start_idx:start_idx + seq_length]
                trg = token_ids[start_idx + 1:start_idx + 1 + seq_length]

                # Padding hinzufügen, falls die Sequenz zu kurz ist
                if len(src) < seq_length:
                    src += [vocab["<pad>"]] * (seq_length - len(src))
                if len(trg) < seq_length:
                    trg += [vocab["<pad>"]] * (seq_length - len(trg))

                self.data.append((src, trg))

        if len(self.data) == 0:
            raise ValueError("Keine gültigen Trainingsbeispiele generiert. Überprüfe seq_length und die Texte.")

    def __len__(self):
        return len(self.data)

    def __getitem__(self, idx):
        src, trg = self.data[idx]
        src = torch.tensor(src, dtype=torch.long)
        trg = torch.tensor(trg, dtype=torch.long)
        return src, trg





def generate_and_train_transformer(raw_texts,
                                   num_epochs = 1,
                                   seq_length = 20):
    """
    Generate a simple Transformer model and train it on a text dataset.
    """

    
    embed_size = 128
    num_layers = 6
    max_length = 50

    # 1. learn a vocabulary from the training texts
    logging.info("Bereite Trainingsdaten für den Transformer vor.")
    vocab = build_vocab(raw_texts)
    logging.info(f"Länge des gelernten Vokabulars: {len(vocab)}")
    vocab_as_text = ""
    for nr, (token, idx) in enumerate(vocab.items()):
        vocab_as_text += f"\n\t{token}: {idx}"
        if nr == 30:
            break
    logging.info(f"\nVokabular:{vocab_as_text}")


    # 2. create a dataset and a dataloader from the raw texts
    src_vocab_size = len(vocab)
    trg_vocab_size = len(vocab)
    dataset = TextDataset(raw_texts, vocab, seq_length)
    batch_size = 32
    dataloader = DataLoader(dataset, batch_size=batch_size, shuffle=True)
    logging.info("\nBeispiel-Daten aus dem Dataloader:")
    for src, trg in dataloader:
        logging.info("src=" + str(src))
        logging.info("trg=" + str(trg))


    # 3. create a simple transformer model
    model = SimpleTransformer(embed_size, src_vocab_size, trg_vocab_size, num_layers, max_length).to(device)
    optimizer = torch.optim.Adam(model.parameters(), lr=0.001)
    criterion = nn.CrossEntropyLoss(ignore_index=vocab["<pad>"])
    
    src_example = torch.randint(0, len(vocab), (32, 20)).to(device)
    trg_example = torch.randint(0, len(vocab), (32, 20)).to(device)    
    torchinfo.summary(model, input_size=[src_example.shape, trg_example.shape], dtypes=[torch.long, torch.long])
    

    # 4. train the transformer
    model.train()
    for epoch in range(num_epochs):
        logging.info(f"Starte Training der Epoche {epoch + 1} von {num_epochs}")
        epoch_loss = 0
        for src, trg in dataloader:
            src, trg = src.to(device), trg.to(device)            
            trg_input = trg[:, :-1]
            trg_output = trg[:, 1:]
            
            # forward pass
            output = model(src, trg_input)
            output = output.reshape(-1, trg_vocab_size)
            trg_output = trg_output.reshape(-1)
            
            # compute loss
            loss = criterion(output, trg_output)

            # backpropagation
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()

            epoch_loss += loss.item()

        print(f"Epoch {epoch + 1}/{num_epochs}, Loss: {epoch_loss / len(dataloader):.4f}")

    return model, vocab


def predict(model, start_text, vocab, max_length=20):
    """
    Use a model and a given start text to predict new tokens.
    """

    model.eval()  # Set the model to evaluation mode
    vocab_reverse = {idx: token for token, idx in vocab.items()}

    # Tokenize and convert start_text to tensor
    tokens = ["<sos>"] + tokenize(start_text)
    token_ids = [vocab.get(token, vocab["<unk>"]) for token in tokens]
    input_tensor = torch.tensor(token_ids, dtype=torch.long).unsqueeze(0).to(device)

    # Start generation loop
    generated_ids = token_ids
    for _ in range(max_length):
        trg_input = torch.tensor(generated_ids, dtype=torch.long).unsqueeze(0).to(device)
        output = model(input_tensor, trg_input)
        next_token_logits = output[0, -1, :]  # Take the last output step
        next_token_id = torch.argmax(next_token_logits).item()

        if next_token_id == vocab["<eos>"]:
            break  # Stop if the model predicts the end of sequence token

        generated_ids.append(next_token_id)

    # Convert token IDs back to text
    generated_tokens = [vocab_reverse[id] for id in generated_ids if id in vocab_reverse]
    return " ".join(generated_tokens)



raw_texts = ["Die Vorlesung Deep Learning ist super.",
             "Die Vorlesung findet im Raum S0.12ab statt.",
             "Die Vorlesung findet um 8 und um 10 Uhr statt.",
             "Die Vorlesung findet immer nur Dienstags statt.",
             "Die Vorlesung wird von Prof. Brauer gehalten.",
             "Die Vorlesung könnte besser sein."]
logging.info("\nHier ein paar Beispiele für Trainingsdaten:\n\t" + "\n\t".join(raw_texts[:10]))
model, vocab = generate_and_train_transformer(raw_texts, num_epochs=50)

start_text = "Die Vorlesung findet"

for _ in range(5):
    generated_text = predict(model, start_text, vocab, max_length=10)
    logging.info(f"Generated Text: {generated_text}")
    print(f"Generated Text: {generated_text}")