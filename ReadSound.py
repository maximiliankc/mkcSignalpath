import SoundIo
import sys

def main(argv):
    io = SoundIo.SoundIo()
    io.read_sound(argv)
    io.analyse()

if __name__ == "__main__":
    if len(sys.argv) == 1:
        input = sys.stdin.read().split()
    else:
       input = sys.argv[1:]
    main(input)
