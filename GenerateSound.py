import SoundIo

def main():
    time = 0.01
    io = SoundIo.SoundIo()
    io.sinusoid(channel=0, duration=time)
    io.noise(channel=1, duration=time)
    io.display_sound()

if __name__ == "__main__":
    main()
