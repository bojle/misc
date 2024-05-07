#include "onnx.pb.h"
#include <string>

/* Onnx Parser external interface */
namespace Op {

struct LayerBase {
  virtual const char *op_type() const;
};

struct ConvParams {
  int imap[2];
  int kn;
  int k[2];
  int pad[4];
  int stride[2];
};

void extract_conv_attr(onnx::NodeProto &node, ConvParams &params);

namespace Layer {

struct Conv : public LayerBase {
  const char *m_optype = "Conv";
  int m_iw;
  int m_ih;
  int m_kn;
  int m_k;
  Conv(int iw, int ih, int kn, int k);
  const char *op_type() const override;
};

struct Relu : public LayerBase {
  const char *m_optype = "Relu";
  int m_clip;
  Relu(int clip);
  const char *op_type() const override;
};

} // namespace Layer

class Model {
  /* OpLayer array defines the entire neural network */
  std::vector<LayerBase *> layers;

public:
  void add(LayerBase *layer);
  LayerBase *operator[](size_t idx);
  LayerBase const *operator[](size_t idx) const;
  size_t size(void);
  size_t size(void) const;
  ~Model();
};

class Parser {
  Model m_model;

public:
  Model &get_model();
  Parser(std::string filename);
  void summary(void) const;
};

} // namespace Op
