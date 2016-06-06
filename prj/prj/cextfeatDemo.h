#ifndef __CEXTFEAT_H
#define __CEXTFEAT_H

#include "cextfeatInt.h"

class CExtfeatDemo : public CExtfeatInt
{
	/* ctor and de-ctor */
public:

	/* interface */
public:
	void doit( ImgWrap *imgWrapSrc1, ImgWrap *imgWrapSrc2, CFeatureStore *featStore ) override;

	/* member fun */
private:
	void _do( ImgWrap *imgWrapSrc1, ImgWrap *imgWrapSrc2, CFeatureStore *featStore );

	/* member var */
private:
};

#endif