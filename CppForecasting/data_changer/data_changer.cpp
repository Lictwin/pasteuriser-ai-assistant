#include "data_changer.h"

void parsing_data_per_cid(data_vector in_data, data_vector out_data, __int8 cid) {
	in_data.clear();
	for (auto datum : out_data) {
		if (datum.cid == cid) 
			in_data.push_back(datum);
	}
}

size_t find_max_element_before_border(const data_vector& data, size_t border, size_t i) {
	if(i < 0) 
		i = 0;
	while (i < data.size()) {
		if (data[i].time > border) {
			i -= 1;
			break;
		}
		i = i + 1;
	}
	if (i == data.size())
		return -1;
	else
		return i;
}

void right_range(data_vector& data, int range) {
	size_t intervals = int((data[data.size() - 1].time - data[0].time) / range);
	__int8 temp_cid = data[0].cid;
	size_t time_0 = data[0].time;
	data_vector temp_data (intervals);
	for (int i = 0; i < intervals; i++) {
		temp_data[i].cid = temp_cid;
		temp_data[i].time = i * range;
	}
	size_t up = 0;
	size_t down = 0;
	for (int i = 0; i < intervals; i++) {
		down = find_max_element_before_border(data, temp_data[i].time, down);
		up = down + 1;
		if (data[down].time == temp_data[i].time) {
			temp_data[i].value = data[down].value;
			continue;
		}
		if (data[up].time == temp_data[i].time) {
			temp_data[i].value = data[up].value;
			continue;
		}
		if (down == data.size() - 1) {
			temp_data[i].value = data[down].value;
			break;
		}
		double tega = double(temp_data[i].time - data[down].time) 
			/ (double(temp_data[i].time - data[down].time) + double(data[up].time - temp_data[i].time));
		double unta = 1 - tega;
		temp_data[i].value = unta * data[down].value + tega * data[up].value;
	}
	data.clear();
	std::copy(temp_data.begin(), temp_data.end(), std::back_inserter(data));
}
