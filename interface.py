import ctypes


class Interface:
    ''' Class for interfacing with interface.so'''
    def __init__(self):
        library = ctypes.CDLL('interface.so')
        self.interface = library.run

    def run(self, input: list):
        length = len(input[0])

        io_vector = length*ctypes.c_float

        # see interface.c
        input_spec = [ctypes.c_int, io_vector, io_vector, io_vector, io_vector]
        self.interface.argtypes = input_spec

        out1 = io_vector()
        out2 = io_vector()

        self.interface(length, io_vector(*input[0]), io_vector(*input[1]),
                       out1, out2)
        return [list(out1), list(out2)]


def main():
    c1 = [1, 2, 3, 4, 5]
    c2 = [4, 5, 6, 7, 8]
    interface = Interface()
    out = interface.run([c1, c2])
    print(out)


if __name__ == "__main__":
    main()
