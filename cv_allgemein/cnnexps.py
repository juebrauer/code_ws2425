import torch
from torchvision.datasets import ImageFolder
from torch.utils.data import DataLoader, random_split
import torchvision.transforms as transforms
import torch.nn as nn
import torch.nn.functional as F
from torchinfo import summary
import matplotlib.pyplot as plt


IMG_SIZE = 128


class CNNModel(nn.Module):
   
    def __init__(self, num_classes):
        super(CNNModel, self).__init__()
        self.conv1 = nn.Conv2d(3, 32, kernel_size=3, stride=1, padding=1)
        self.conv2 = nn.Conv2d(32, 64, kernel_size=3, stride=1, padding=1)
        self.conv3 = nn.Conv2d(64, 128, kernel_size=3, stride=1, padding=1)
        self.conv4 = nn.Conv2d(128, 256, kernel_size=3, stride=1, padding=1)
        self.conv5 = nn.Conv2d(256, 512, kernel_size=3, stride=1, padding=1)
        self.pool = nn.MaxPool2d(kernel_size=2, stride=2)
        
        # Die Größe der Eingabe für fc1 dynamisch bestimmen
        self._initialize_fc_layers(IMG_SIZE)

        self.fc1 = nn.Linear(self.fc_input_size, 512)
        self.fc2 = nn.Linear(512, num_classes)
    
    def _initialize_fc_layers(self, img_size):
        # Ein Dummy-Forward-Pass, um die Größe der Ausgabe nach den Conv- und Pooling-Layern zu bestimmen
        with torch.no_grad():
            x = torch.zeros((1, 3, img_size, img_size))  # Ein Dummytensor mit den Eingabedimensionen
            x = self.feature_extractor(x)  # Verwende die neue Methode
            self.fc_input_size = x.view(-1).shape[0]  # Bestimme die Größe nach dem Flatten

    def feature_extractor(self, x):
        # Dieser Teil des Netzwerks führt die Convolution- und Pooling-Schritte aus
        x = self.pool(F.relu(self.conv1(x)))
        x = self.pool(F.relu(self.conv2(x)))
        x = self.pool(F.relu(self.conv3(x)))
        x = self.pool(F.relu(self.conv4(x)))
        x = self.pool(F.relu(self.conv5(x)))
        return x

    def forward(self, x):
        x = self.feature_extractor(x)  # Verwende die neue Methode
        x = x.view(x.size(0), -1)  # Flatten
        x = F.relu(self.fc1(x))
        x = self.fc2(x)
        #x = torch.softmax(x, dim=1)
        return x



def prepare_dataset(data_dir):

    # Transformationen für die Bilder
    transform = transforms.Compose([
        transforms.Resize((IMG_SIZE, IMG_SIZE)),  # Bildgröße anpassen
        transforms.ToTensor(),         # In Tensor umwandeln
        transforms.Normalize(mean=[0.5, 0.5, 0.5], std=[0.5, 0.5, 0.5])  # Normalisierung
    ])
    
    # Gesamter Datensatz
    full_dataset = ImageFolder(root=data_dir, transform=transform)
    
    # Aufteilen in Training (90%) und Test (10%)
    test_size = int(0.1 * len(full_dataset))
    train_size = len(full_dataset) - test_size
    
    train_dataset, test_dataset = random_split(full_dataset, [train_size, test_size])
    
    # DataLoader für Training und Test
    train_loader = DataLoader(train_dataset, batch_size=32, shuffle=True)
    test_loader = DataLoader(test_dataset, batch_size=32, shuffle=False)
    
    print(f"Training samples: {len(train_dataset)}, Test samples: {len(test_dataset)}")

    nr_classes = len(full_dataset.classes)
    
    return nr_classes, train_loader, test_loader


def test_model(model, device, test_loader):
    model.eval()  # Modell in Evaluationsmodus
    correct = 0
    total = 0
    
    with torch.no_grad():
        for images, labels in test_loader:
            images, labels = images.to(device), labels.to(device)
            outputs = model(images)
            _, predicted = torch.max(outputs, 1)
            total += labels.size(0)
            correct += (predicted == labels).sum().item()

    acc = 100 * correct / total
    print(f"Accuracy: {acc:.2f}%")
    return acc
    

def create_and_train_model(nr_classes, train_loader, test_loader, nr_epochs):

    # Modell initialisieren    
    model = CNNModel(nr_classes)

    import torch.optim as optim
    criterion = nn.CrossEntropyLoss()
    optimizer = optim.Adam(model.parameters(), lr=0.001)
    
    device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
    model.to(device)
    
    model_txt = summary(model, input_size=(1, 3, IMG_SIZE, IMG_SIZE))
    print(model_txt)    
        
    accs = []
    num_epochs = 20
    for epoch in range(nr_epochs):
        print(f"epoch {epoch+1} of {nr_epochs}")
        model.train()  # Modell in Trainingsmodus
        running_loss = 0.0
    
        batch_nr = 0
        for images, labels in train_loader:
            images, labels = images.to(device), labels.to(device)
            
            # Vorwärts, Rückwärts, Optimieren
            optimizer.zero_grad()
            
            outputs = model(images) # Logits
            print(f"{outputs.shape=}")
            print(f"{outputs=}")
            
            
            loss = criterion(outputs, labels)
            print(f"{loss.shape=}")
            print(f"{loss=}")

            exit()
            
            loss.backward()
            optimizer.step()
            
            running_loss += loss.item()
    
            batch_nr += 1
    
            if batch_nr % 100 == 0:
                print(f"{batch_nr=} ", end=" ")
        
        print(f"Epoch {epoch+1}/{nr_epochs}, Loss: {running_loss/len(train_loader):.4f}")
    
        acc = test_model(model, device, test_loader)
        accs.append( acc )
        
    plt.title("Lernkurve")
    plt.xlabel("Epoche")
    plt.ylabel("Klassifikationsgenauigkeit")
    plt.plot( accs )
    plt.show()
    
    torch.save(model.state_dict(), 'cnn_animal10.pth')
    print("Modell gespeichert!")