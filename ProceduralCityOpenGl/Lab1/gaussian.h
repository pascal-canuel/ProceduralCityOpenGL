#pragma once

struct Gaussian {
	Gaussian() {};
	float kernel[20][20];


	void getGaussianKernel(int rows, int cols, double sigmax, double sigmay)
	{

		const auto y_mid = (rows - 1) / 2.0;
		const auto x_mid = (cols - 1) / 2.0;

		const auto x_spread = 1. / (sigmax*sigmax * 2);
		const auto y_spread = 1. / (sigmay*sigmay * 2);

		const auto denominator = 8 * std::atan(1) * sigmax * sigmay;

		std::vector<double> gauss_x, gauss_y;

		gauss_x.reserve(cols);
		for (auto i = 0; i < cols; ++i) {
			auto x = i - x_mid;
			gauss_x.push_back(std::exp(-x * x * x_spread));
		}

		gauss_y.reserve(rows);
		for (auto i = 0; i < rows; ++i) {
			auto y = i - y_mid;
			gauss_y.push_back(std::exp(-y * y * y_spread));
		}
	
		for (auto j = 0; j < rows; ++j)
			for (auto i = 0; i < cols; ++i) {
				kernel[j][i] = (gauss_x[i] * gauss_y[j] / denominator) * 1000;
			}
	}
};