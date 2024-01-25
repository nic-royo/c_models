#define MLPACK_PRINT_INFO
#define MLPACK_PRINT_WARN
#include <mlpack.hpp>

using namespace arma;
using namespace mlpack;
using namespace mlpack::cf;
using namespace std;

int main()
{
  // Load the ratings.
  mat ratings;
  if (!data::Load("ratings-only.csv", ratings))
    throw std::runtime_error("Could not load ratings-only.csv!");
  // Now, load the names of the movies as a single-feature categorical dataset.
  // We can use `moviesInfo.UnmapString(i, 0)` to get the i'th string.
  data::DatasetInfo moviesInfo;
  mat movies; // This will be unneeded.
  if (!data::Load("movies.csv", movies, moviesInfo))
    throw std::runtime_error("Could not load movies.csv!");

  // Split the ratings into a training set and a test set, using 10% of the
  // dataset for the test set.
  mat trainRatings, testRatings;
  data::Split(ratings, trainRatings, testRatings, 0.1);

  // Train the CF model using RegularizedSVD as the decomposition algorithm.
  // Here we use a rank of 10 for the decomposition.
  CFType<RegSVDPolicy> cf(
      trainRatings,
      RegSVDPolicy(),
      5, /* number of users to use for similarity computations */
      10 /* rank of decomposition */);

  // Now compute the RMSE for the test set user and item combinations.  To do
  // this we must assemble the list of users and items.
  Mat<size_t> combinations(2, testRatings.n_cols);
  for (size_t i = 0; i < testRatings.n_cols; ++i)
  {
    combinations(0, i) = size_t(testRatings(0, i)); // (user)
    combinations(1, i) = size_t(testRatings(1, i)); // (item)
  }
  vec predictions;
  cf.Predict(combinations, predictions);
  const double rmse = norm(predictions - testRatings.row(2).t(), 2) /
      sqrt((double) testRatings.n_cols);
  std::cout << "RMSE of trained model is " << rmse << "." << endl;

  // Compute the top 10 movies for user 1.
  Col<size_t> users = { 1 };
  Mat<size_t> recommendations;
  cf.GetRecommendations(10, recommendations, users);

  // Now print each movie.
  cout << "Recommendations for user 1:" << endl;
  for (size_t i = 0; i < recommendations.n_elem; ++i)
  {
    cout << "  " << (i + 1) << ". "
        << moviesInfo.UnmapString(recommendations[i], 2) << "." << endl;
  }
}

// g++ -O3 -std=c++14 -o attempt attempt.cpp -fopenmp -larmadillo
// ./attempt