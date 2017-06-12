/*
 * shiftreg.h
 *
 *  Created on: 2. mai 2017
 *      Author: Y009
 */

#ifndef SRC_SHIFTREG_H_
#define SRC_SHIFTREG_H_

#define SIZEOFMATR 16       // Rows and columns the shiftregister is able to display
#define SIZEOFRAWMATR 14    // LED matrix's columns
#define SIZEOFRAWMATR2 10   // LED matrix's rows

void shiftreg_init();
void shiftreg_exec();
void shiftreg_set_newMatr(unsigned int transfer [SIZEOFRAWMATR2][SIZEOFRAWMATR]);

#endif /* SRC_SHIFTREG_H_ */
