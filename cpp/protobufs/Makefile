all: main.cpp onnx.pb.cc onnx.pb.h
	g++ main.cpp onnx.pb.cc -o a -Wl,--copy-dt-needed-entries -lprotoc -lprotobuf -lpthread 

default: onnx_parser.cpp onnx.pb.cc onnx.pb.h onnx_parser.h
	g++ onnx_parser.cpp onnx.pb.cc -o a -Wl,--copy-dt-needed-entries -lprotoc -lprotobuf -lpthread && ./a /home/metal/dev/vaaman-cnn/onnx/vgg16/vgg16-12.onnx

write: write.cpp test.pb.cc test.pb.h
	g++ $^ -o a -Wl,--copy-dt-needed-entries -lprotoc -lprotobuf -lpthread

# Does not work, as lld doesn not seem to support copy-dt-entries needed
write-lld: write.cpp test.pb.cc test.pb.h
	g++ $^ -o a -fuse-ld=lld -lpthread -lprotoc -lprotobuf 

# Does not work either
write-gold: write.cpp test.pb.cc test.pb.h
	g++ $^ -o a -fuse-ld=gold -Wl,--threads -Wl,--thread-count=8 -Wl,--copy-dt-needed-entries -lprotoc -lprotobuf -lpthread 

read: read.cpp test.pb.cc test.pb.h
	g++ $^ -o b -Wl,--copy-dt-needed-entries -lprotoc -lprotobuf -lpthread

read_onnx: read_onnx.cpp onnx.pb.cc onnx.pb.h
	g++ $^ -o b -Wl,--copy-dt-needed-entries -lprotoc -lprotobuf -lpthread


