import SoundIo

def main():
    io = SoundIo.SoundIo()
    io.sinusoid(duration = 0.01, channel=0)
    io.noise(duration = 0.01, channel=1)
    io.display_sound()

if __name__ == "__main__":
    main()
