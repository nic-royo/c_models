/**
 * @file mlpack.hpp
 *
 * Include all of mlpack!  When this file is included, all components of mlpack
 * are available.
 *
 * Note that by default, serialization for ANN layers is not enabled, since this
 * will cause the build time to be very long.  If you plan to serialize a neural
 * network, simply include mlpack like this:
 *
 * ```
 * #define MLPACK_ENABLE_ANN_SERIALIZATION
 * #include <mlpack.hpp>
 * ```
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#ifndef MLPACK_HPP
#define MLPACK_HPP

// Include all of the core library components.
#include "mlpack/base.hpp"
#include "mlpack/prereqs.hpp"
#include "mlpack/core.hpp"

// Now include all of the methods.
#include "mlpack/methods/adaboost.hpp"
#include "mlpack/methods/preprocess.hpp"
#include "mlpack/methods/random_forest.hpp"


// Include reverse compatibility.
#include "mlpack/namespace_compat.hpp"

#endif