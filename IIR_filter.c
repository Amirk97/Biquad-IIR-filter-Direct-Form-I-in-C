/*
 * IIR_filter.c
 *
 *  Created on: 7 Jul 2022
 *      Author: ak2251
 */
#include "IIR_filter.h"

/* This function resets the content of all buffers to zero
 */
void init_filter(filter* IIR_filter) {

	for(uint8_t i=0; i<INPUT_BUFFER_LENGTH; i++) {

		IIR_filter->input_buffer[i] = 0;
	}

	for(uint8_t i=0; i<OUTPUT_BUFFER_LENGTH; i++) {

		IIR_filter->output_buffer[i] = 0;
	}

	IIR_filter->input_buffer_index = 0;
	IIR_filter->output_buffer_index = 0;

	IIR_filter->output = 0;
}

double compute_filter_output(filter* IIR_filter, double input) {

	int8_t saved_index ;

	/* Insert the input in the input buffer */
	IIR_filter->input_buffer[IIR_filter->input_buffer_index] = input;

	/* Update Buffer Index */
	IIR_filter->input_buffer_index ++;
	if(IIR_filter->input_buffer_index == INPUT_BUFFER_LENGTH) {

		IIR_filter->input_buffer_index = 0;
	}

	/* Reset output */
	IIR_filter->output = 0;

	/* Make a copy of input buffer index so we can manipulate it */
	saved_index = IIR_filter->input_buffer_index;

	/* Computing the product of multiplication between input buffer and corresponding coefficients */
	for(uint8_t i =0; i<INPUT_BUFFER_LENGTH; i++) {

		saved_index --;
		if(saved_index < 0) {
			saved_index = INPUT_BUFFER_LENGTH-1;
		}

		IIR_filter->output += (IIR_filter->input_coeff[i] * IIR_filter->input_buffer[saved_index]);
	}

	/* Make a copy of output buffer index so we can manipulate it */
	saved_index = IIR_filter->output_buffer_index;

	/* Computing the product of multiplication between output buffer and corresponding coefficients */
	for(uint8_t i =0; i<OUTPUT_BUFFER_LENGTH; i++) {

		saved_index --;
		if(saved_index < 0) {
			saved_index = OUTPUT_BUFFER_LENGTH-1;
		}
		IIR_filter->output -= (IIR_filter->output_coeff[i] * IIR_filter->output_buffer[saved_index]);
	}

	/* Insert the calculated output into output buffer */
	IIR_filter->output_buffer[IIR_filter->output_buffer_index] = IIR_filter->output;

	/* Update output Buffer Index */
	IIR_filter->output_buffer_index ++;
	if(IIR_filter->output_buffer_index == OUTPUT_BUFFER_LENGTH) {

		IIR_filter->output_buffer_index = 0;
	}

	return IIR_filter->output;
}
