#ifndef MXNETCPP_OPTIMIZER_H
#define MXNETCPP_OPTIMIZER_H

#include <map>
#include "base.h"
#include "logging.h"
#include "ndarray.h"

namespace mxnet {
namespace cpp {

/*!
* \brief Optimizer interface
*/
class Optimizer {
public:
  /*!
  * \brief Operator constructor, the optimizer is not initialized until the first Update
  * \param opt_type type of the optimizer
  */
  explicit Optimizer(const std::string &opt_type);
  /*!
  * \brief destructor, free the handle
  */
  ~Optimizer() {
    if (init_) MXOptimizerFree(handle_);
  }
  /*!
  * \brief set config parameters
  * \param name name of the config parameter
  * \param value value of the config parameter
  * \return reference of self
  */
  template <typename T>
  Optimizer &SetParam(const std::string &name, const T &value) {
    std::string value_str;
    std::stringstream ss;
    ss << value;
    ss >> value_str;

    params_[name] = value_str;
    return *this;
  }
  /*!
  *  \brief Update a weight with gradient.
  *  \param index the unique index for the weight.
  *  \param weight the weight to update.
  *  \param grad gradient for the weight.
  *  \param lr learning rate for this update.
  */
  void Update(int index, NDArray weight, NDArray grad, mx_float lr);
  // TODO(zhangcheng-qinyinghua)
  // implement Update a list of arrays, maybe in the form of map
  //void Update(int index, std::vector<NDArray> weights, std::vector<NDArray> grad, mx_float lr);

private:
  bool init_;
  Optimizer(const Optimizer &);
  Optimizer &operator=(const Optimizer &);
  OptimizerHandle handle_;
  OptimizerCreator creator_;
  std::map<std::string, std::string> params_;
};

}
}

#endif // MXNETCPP_OPTIMIZER_H