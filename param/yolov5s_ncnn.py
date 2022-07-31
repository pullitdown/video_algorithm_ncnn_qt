import numpy as np
import ncnn
import torch

def test_inference():
    torch.manual_seed(0)
    in0 = torch.rand(1, 3, -1, -1, dtype=torch.float)
    out = []

    with ncnn.Net() as net:
         net.load_param("/home/stepf/world/video_algorithm_ncnn_qt/param/yolov5s.ncnn.param")
         net.load_model("/home/stepf/world/video_algorithm_ncnn_qt/param/yolov5s.ncnn.bin")

         with net.create_extractor() as ex:
            ex.input("in0", ncnn.Mat(in0.squeeze(0).numpy()).clone())

            _, out0 = ex.extract("out0")
            out.append(torch.from_numpy(np.array(out0)).unsqueeze(0))
            _, out1 = ex.extract("out1")
            out.append(torch.from_numpy(np.array(out1)).unsqueeze(0))
            _, out2 = ex.extract("out2")
            out.append(torch.from_numpy(np.array(out2)).unsqueeze(0))

    if len(out) == 1:
        return out[0]
    else:
        return tuple(out)
