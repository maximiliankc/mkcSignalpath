import SoundIo


def main():
    time = 10
    io = SoundIo.SoundIo()
    io.sinusoid(channel=0, duration=time)
    io.noise(channel=1, duration=time)
    io.display_sound()


if __name__ == "__main__":
    main()
