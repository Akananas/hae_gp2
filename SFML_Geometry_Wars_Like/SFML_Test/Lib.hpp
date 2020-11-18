#pragma once

#include <chrono>
#include <ctime>

using namespace std;
using namespace std::chrono;

namespace Lib {
	//in secs
	double getTimeStamp() //retourne le temps actuel en seconde
	{
		std::chrono::nanoseconds ns =
			duration_cast<std::chrono::nanoseconds>(system_clock::now().time_since_epoch());
		return ns.count() / 1000000000.0;
	}
	void m_gaussian_kernel(float* dest, int size, float radius)
	{
		float* k;
		float rs, s2, sum;
		float sigma = 1.6f;
		float tetha = 2.25f;
		int r, hsize = size / 2;

		s2 = 1.0f / expf(sigma * sigma * tetha);
		rs = sigma / radius;

		k = dest;
		sum = 0.0f;

		/* compute gaussian kernel */
		for (r = -hsize; r <= hsize; r++) {
			float x = r * rs;
			float v = (1.0f / expf(x * x)) - s2;
			v = std::max(v, 0.0f);
			*k = v;
			sum += v;
			k++;
		}

		/* normalize */
		if (sum > 0.0f) {
			float isum = 1.0f / sum;
			for (r = 0; r < size; r++)
				dest[r] *= isum;
		}
	}
}
