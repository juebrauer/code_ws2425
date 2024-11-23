with open("openai_api_key.txt", "rt") as f:
    key = f.read()
    
from openai import OpenAI
client = OpenAI(api_key=key)

def text_to_speech(text, playsound=True, selected_voice="shimmer"):
    
    # Other voices that could be chosen:
    # "alloy", "echo", "fable", "onyx", "nova", "shimmer"
    

    with client.audio.speech.with_streaming_response.create(
        model="tts-1",
        voice=selected_voice,
        input=text,
    ) as response:
        # This doesn't seem to be *actually* streaming, it just creates the file
        # and then doesn't update it until the whole generation is finished
        response.stream_to_file(f"tmp_speech.mp3")

    if playsound:
        from pydub import AudioSegment
        import simpleaudio as sa

        # Laden der MP3-Datei
        song = AudioSegment.from_mp3("tmp_speech.mp3")

        # Abspielen der MP3-Datei
        play_obj = sa.play_buffer(song.raw_data, num_channels=song.channels, bytes_per_sample=song.sample_width, sample_rate=song.frame_rate)
        play_obj.wait_done()  # Warten, bis das Abspielen beendet ist


ki_programmierung = """Du bist ein Studierendenberater für die Hochschule Kempten.
Studierende mögen kurze Antworten. Halte dich in deinen Antworten daher sehr sehr kurz!
"""

alle_nachrichten = [
                    {"role"    : "system",
                     "content" : ki_programmierung,
                    }
                   ]

while True:
    anfrage = input("<<< ")

    if anfrage == "tschuess":
        break

    neue_nachricht = {"role" : "user", "content" : anfrage}
    alle_nachrichten.append( neue_nachricht )

    chat_completion = client.chat.completions.create(
        model="gpt-4o-mini",
        messages=alle_nachrichten        
    )

    antwort = chat_completion.choices[0].message.content
    print(f">>> {antwort}")
    text_to_speech( antwort )