//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//
//
//
//#pragma once
//	
//
//#include "ofx/DOM/Events.h"
//
//
//namespace ofx {
//namespace MUI {
//
//
////    class Button;
////
////
////    class ButtonEventArgs: public DOM::EventArgs
////    {
////    public:
////        /// \brief Create EventArgs with a type.
////        /// \param type The event type string (case-insensitive).
////        /// \param source The source of the event.
////        /// \param target The target element.
////        /// \param relatedTarget The relatedTarget element.
////        /// \param bubbles True iff the argument bubbles after AT_TARGET phase.
////        /// \param cancelable True iff the event can be cancelled by a listener.
////        /// \param timestamp The timestamp of the event.
////        ButtonEventArgs(const std::string& type,
////                        Button* source,
////                        Button* target,
////                        Widget* relatedTarget,
////                        bool bubbles,
////                        bool cancelable,
////                        uint64_t timestamp);
////
////
////
////        static const std::string BUTTON_DOWN;
////        static const std::string BUTTON_UP;
////        static const std::string BUTTON_PRESSED;
////        
////    private:
////        Button* _button;
////        Widget* _parent;
////        
////    };
//
//
//} } // ofx::MUI
