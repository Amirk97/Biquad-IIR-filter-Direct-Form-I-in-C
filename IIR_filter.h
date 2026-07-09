/*
 * IIR_filter.h
 *
 *  Created on: 7 Jul 2022
 *      Author: ak2251
 */
#ifdef __cplusplus
extern "C" {
#endif

#ifndef SRC_IIR_FILTER_H_
#define SRC_IIR_FILTER_H_

#include "stdint.h"

#define INPUT_BUFFER_LENGTH 3
#define OUTPUT_BUFFER_LENGTH 2


typedef struct {
	double input_buffer[INPUT_BUFFER_LENGTH];
	uint8_t input_buffer_index;

	double output_buffer[OUTPUT_BUFFER_LENGTH];
	uint8_t output_buffer_index;

	double output;

  float input_coeff[INPUT_BUFFER_LENGTH];
  float output_coeff[OUTPUT_BUFFER_LENGTH];

}filter;


void init_filter(filter *);
double compute_filter_output(filter* , double );

#endif /* SRC_IIR_FILTER_H_ */

  
#ifdef __cplusplus
}
#endif  
