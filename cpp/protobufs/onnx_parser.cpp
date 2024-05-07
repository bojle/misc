#include "onnx.pb.h"
#include "onnx_parser.h"
#include <fstream>
#include <iostream>

const char *Op::LayerBase::op_type() const { return "(null)"; }

Op::Layer::Conv::Conv(int iw, int ih, int kn, int k)
    : m_iw{iw}, m_ih{ih}, m_kn{kn}, m_k{k} {}
const char *Op::Layer::Conv::op_type() const { return m_optype; }

Op::Layer::Relu::Relu(int clip) : m_clip{clip} {}
const char *Op::Layer::Relu::op_type() const { return m_optype; }

void Op::Model::add(Op::LayerBase *layer) { layers.push_back(layer); }
Op::LayerBase *Op::Model::operator[](size_t idx) { return layers.at(idx); }
Op::LayerBase const *Op::Model::operator[](size_t idx) const {
  return layers.at(idx);
}
Op::Model::~Model() {
  for (int i = 0; i < layers.size(); ++i) {
    delete layers.at(i);
  }
}

size_t Op::Model::size(void) { return layers.size(); }

size_t Op::Model::size(void) const { return layers.size(); }

Op::Model &Op::Parser::get_model() { return m_model; }

void parse_onnx_ints(onnx::AttributeProto &attr, int *attr_array) {
  assert(attr.type() == onnx::AttributeProto::INTS &&
         "expected attributes of type INTS");
  auto ints = attr.ints();
  for (int i = 0; i < ints.size(); ++i) {
    attr_array[i] = ints.at(i);
  }
}

void Op::extract_conv_attr(onnx::NodeProto &node, Op::ConvParams &params) {
  auto attribute = node.attribute();
  for (auto itr = attribute.begin(); itr != attribute.end(); ++itr) {
    if (itr->name() == "kernel_shape") {
      assert(itr->ints().size() == 2 &&
             "expected kernel shape to be 2 integers");
      parse_onnx_ints(*itr, params.k);
    } else if (itr->name() == "strides") {
      assert(itr->ints().size() == 2 &&
             "expected strides shape to be 2 integers");
      parse_onnx_ints(*itr, params.stride);
    } else if (itr->name() == "pads") {
      assert(itr->ints().size() == 4 && "expected pads shape to be 4 integers");
      parse_onnx_ints(*itr, params.pad);
    }
  }
}

Op::Parser::Parser(std::string filename) {
  std::fstream in(filename, std::ios::in | std::ios::binary);
  onnx::ModelProto p;
  p.ParseFromIstream(&in);
  onnx::GraphProto graph = p.graph();
  auto nodes = graph.node();

  for (int i = 0; i < nodes.size(); ++i) {
    auto opt = nodes.at(i).op_type();
    if (opt == "Conv") {
      ConvParams params;
      extract_conv_attr(nodes.at(i), params);
      m_model.add(new Op::Layer::Conv(1, 2, 3, 4));
    }
    if (opt == "Relu") {
      m_model.add(new Op::Layer::Relu(10));
    }
  }
}

void Op::Parser::summary() const {
  for (int i = 0; i < m_model.size(); ++i) {
    std::cout << m_model[i]->op_type() << '\n';
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Too few arguments" << '\n';
    return 1;
  }

  Op::Model m;
  m.add(new Op::Layer::Conv(224, 224, 64, 3));
  m.add(new Op::Layer::Relu(10));
  std::cout << m[0]->op_type() << '\n';
  std::cout << m[1]->op_type() << '\n';
  Op::Parser parser(argv[1]);
  parser.summary();
}
