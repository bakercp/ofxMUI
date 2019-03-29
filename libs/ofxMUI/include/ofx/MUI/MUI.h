//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once
	

#include "ofx/DOM/Document.h"


namespace ofx {
namespace MUI {


class Styles;


class MUI: public DOM::Document
{
public:
    enum Scale
    {
        SMALL,
        MEDIUM,
        LARGE,
        X
    };

    MUI(ofAppBaseWindow* window = nullptr);
	virtual ~MUI();


	std::shared_ptr<Styles> getDocumentStyles() const;
    
	void setDocumentStyles(std::shared_ptr<Styles> documentStyles);

protected:
	mutable std::shared_ptr<Styles> _documentStyles;

};


} } // ofx::MUI
