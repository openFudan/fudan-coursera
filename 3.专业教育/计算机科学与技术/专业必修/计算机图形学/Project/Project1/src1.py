import wave
import pylab as pl
import numpy as np

# 打开WAV文档
f = wave.open(r"summer.wav", "rb")

# 读取格式信息
params = f.getparams()
nchannels, sampwidth, framerate, nframes = params[:4]

# 读取波形数据
source_data = f.readframes(nframes)
f.close()

#转换波形数据
wave_data = np.fromstring(source_data, dtype=np.short)
wave_data.shape = -1, 2
wave_data = wave_data.T

#计算取样时间：
samplingtime = np.arange(0, nframes) * (1.0 / framerate)

# 绘制波形
pl.subplot(211)
pl.plot(samplingtime, wave_data[0])
pl.subplot(212)
pl.plot(samplingtime, wave_data[1], c="g")
pl.xlabel("samplingtime (seconds)")
pl.show()
