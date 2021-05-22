
# should print out an audio file in [channels, len, fs, [channel 1 in PCM float [0,1]], ... , [channel n in PCM float [0,1]]]

import numpy as np
import scipy.signal as s
import matplotlib.pyplot as plt

class SoundIo:
    filename = ''
    fs = 48000
    sound = {}

    def display_sound(self):
        print(len(self.sound), end=' ')
        print(len(self.sound[0]), end=' ')
        print(self.fs, end=' ')
        for c in self.sound:
            for sample in self.sound[c]:
                print(sample, end=' ')
    
    def read_sound(self, argv):
        channels = int(argv[0])
        length = int(argv[1])
        self.fs = float(argv[2])

        for n in range(channels):
            index1 = length*n
            index2 = length*(n+1)
            stream = argv[3+index1:3+index2]
            self.sound[n] = np.array(stream).astype(float)

    def analyse(self):
        for c in self.sound:
            stream = self.sound[c]
            self.plot_time(stream, c)
            self.plot_spectrogram(stream, c)
            self.plot_periodogram(stream, c)
        plt.show()
    
    def plot_time(self, stream, c):
        _, ax = plt.subplots()
        t = np.arange(0, len(stream)/self.fs, 1/self.fs)
        ax.plot(t, stream)
        ax.set_xlabel('Time (s)')
        ax.set_ylabel('Magnitude ([M])')
        ax.set_title(f"Channel {c}")
        ax.grid(True)

    def plot_spectrogram(self, stream, c):
        f, t, Sxx = s.spectrogram(stream, self.fs)
        _, ax = plt.subplots()
        ax.pcolormesh(t, f, Sxx, shading='gouraud')
        ax.set_ylabel('Frequency (Hz)')
        ax.set_xlabel('Time (s)')
        ax.set_title(f"Channel {c}")
    
    def plot_periodogram(self, stream, c, fb=None):
        power = np.sum(stream*stream)/len(stream)
        f, PSD = s.periodogram(stream, self.fs)
        _, ax = plt.subplots()
        ax.plot(f, PSD)
        ax.set_xlabel('PSD ([M]^2/Hz)')
        ax.set_ylabel('Frequency (Hz)')
        title = f"Channel {c}, power = {power:.2f} ([M])^2/s)"
        if fb is not None:
            [fl, fh] = fb
            power_index = (f>=fl) & (f<=fh)
            sum(PSD[power_index])
            ax.axvline(fl, ls="--", c='tab:red')
            ax.axvline(fh, ls="--", c='tab:red')
            title += f", band power = {sum(PSD[power_index]):.2f} ([M]^2/s)"

        ax.set_title(title)

    def sinusoid(self, m=1., f=1000., duration=1, channel=0):
        len = duration*self.fs
        n = np.arange(len)
        self.sound[channel] = m*np.sin(n*2*np.pi*f/self.fs)
    
    def noise(self, p=1, duration=1, channel=0):
        len = duration*self.fs
        self.sound[channel] = p*np.random.randn(len)
    
def main(argv):
    io = SoundIo()
    io.read_sound(argv)
    io.display_sound()

if __name__ == "__main__":
    import sys
    if len(sys.argv) == 1:
        input = sys.stdin.read().split()
    else:
        input = sys.argv[1:]
    main(input)
