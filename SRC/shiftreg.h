/*
 * shiftreg.h
 *
 *  Created on: 2. mai 2017
 *      Author: Y009
 */

#ifndef SRC_SHIFTREG_H_
#define SRC_SHIFTREG_H_

#define SIZEOFMATR 16
#define SIZEOFRAWMATR 14
#define SIZEOFRAWMATR2 10

void shiftreg_init();
void shiftreg_exec();
void shiftreg_set_newMatr(unsigned int transfer [SIZEOFRAWMATR2][SIZEOFRAWMATR]);

#endif /* SRC_SHIFTREG_H_ */
