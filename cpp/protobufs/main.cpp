#include "onnx.pb.h"
#include <fstream>
#include <google/protobuf/arena.h>

class Wrapper {
    google::protobuf::Arena arena;
    onnx::ModelProto *message;
public:
  Wrapper() {
    message = google::protobuf::Arena::CreateMessage<onnx::ModelProto>(&arena);

    std::fstream in("/home/metal/dev/vaaman-cnn/onnx/vgg/vgg16-12.onnx",
                    std::ios::in | std::ios::binary);
    message->ParseFromIstream(&in);
  }
  const onnx::TensorProto& ref() {
    std::cout << "address: " << &(message->graph().initializer(2)) << '\n';
    return message->graph().initializer(2);
  }
};

class Wrapper2 {
    onnx::ModelProto message;
public:
  Wrapper2() {
    std::fstream in("/home/metal/dev/vaaman-cnn/onnx/vgg/vgg16-12.onnx",
                    std::ios::in | std::ios::binary);
    message.ParseFromIstream(&in);
  }

  const onnx::TensorProto& ref() {
    return message.graph().initializer(2);
  }

};



int main() {
  Wrapper w;
  const onnx::TensorProto& new_ref = w.ref();
  std::cout << "address 2: " << &new_ref << '\n';
  std::cout << w.ref().dims_size() << '\n';
  std::cout << new_ref.dims_size() << '\n';
}
