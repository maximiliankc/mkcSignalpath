import SoundIo

def main():
    io = SoundIo.SoundIo()
    io.sinusoid(channel=0)
    io.noise(channel=1)
    io.display_sound()

if __name__ == "__main__":
    main()
