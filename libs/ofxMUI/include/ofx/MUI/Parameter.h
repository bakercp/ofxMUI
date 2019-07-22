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
//#include "ofEvent.h"
//#include "ofParameter.h"
//
//
//namespace ofx {
//namespace MUI {
//
//
///// \brief A Parameter Adapter.
/////
///// Holds data represented by the widget or binds to another parameter.
///// It is possible to bind external ofParameter variables, but it is not
///// possible to un-bind.  To remove the binding, one must recreate the Widget.
/////
///// The primary reason for this wrapper is to abstract the relationship between
///// the data and the view.
/////
///// \tparam Type the data type represented by the Parameter.
//template <typename Type>
//class Parameter
//{
//public:
//    /// \brief Create a default parameter with templated type.
//    Parameter();
//
//    /// \brief Create a parameter that is a reference to the given parameter.
//    /// \param parameter The ofParameter to reference.
//    Parameter(ofParameter<Type> parameter);
//
//    /// \brief Destroy this Widget.
//    virtual ~Parameter();
//
//    /// \brief Bind this adapter to an existing parameter.
//    /// \param parameter The parameter to bind to.
//    void makeReferenceTo(ofParameter<Type>& parameter);
//
//    /// \brief Add listeners to this onValueChanged event.
//    /// \tparam ListenerClass The class type of the listener.
//    /// \tparam ListenerMethod The name of the listener method.
//    /// \param listener A pointer to the listener instance.
//    /// \param method A pointer to the listener method.
//    /// \param prioirty The order priority of this listener.
//    template <class ListenerClass, typename ListenerMethod>
//    void addListener(ListenerClass* listener, ListenerMethod method, int priority = OF_EVENT_ORDER_AFTER_APP)
//    {
//        ofAddListener(onParameterChanged, listener, method, priority);
//    }
//
//    /// \brief Remove listeners to this onValueChanged event.
//    /// \tparam ListenerClass The class type of the listener.
//    /// \tparam ListenerMethod The name of the listener method.
//    /// \param listener A pointer to the listener instance.
//    /// \param method A pointer to the listener method.
//    /// \param prioirty The order priority of this listener.
//    template <class ListenerClass, typename ListenerMethod>
//    void removeListener(ListenerClass* listener, ListenerMethod method, int priority = OF_EVENT_ORDER_AFTER_APP)
//    {
//        ofRemoveListener(onParameterChanged, listener, method, priority);
//    }
//    
//    /// \brief A callback for the parameter change.
//    ofEvent<Type> onParameterChanged;
//
//    /// \brief The assignment operator.
//    /// \param v Value to assign.
//    /// \returns the assigned value.
//    Type operator = (Type v);
//
//    /// \brief Dereference operator.
//    operator const Type& ();
//
//protected:
//    /// \brief A callback for the ParameterWidget's value.
//    /// \param value The the updated value.
//    virtual void _onParameterChanged(const void* sender, Type& value) = 0;
//
//    /// \brief The paremter of to watch.
//    ofParameter<Type> _parameter;
//
//};
//
//
//template <typename Type>
//Parameter<Type>::Parameter()
//{
//    _parameter.addListener(this,
//                           &Parameter<Type>::_onParameterChanged,
//                           std::numeric_limits<Type>::lowest());
//}
//
//
//
//template <typename Type>
//Parameter<Type>::Parameter(ofParameter<Type> parameter):
//    _parameter(parameter)
//{
//    _parameter.addListener(this,
//                           &Parameter<Type>::_onParameterChanged,
//                           std::numeric_limits<Type>::lowest());
//}
//
//
//template <typename Type>
//Parameter<Type>::~Parameter()
//{
//    // Remove the listener from the local or bound parameters.
//    _parameter.removeListener(this,
//                              &Parameter<Type>::_onParameterChanged,
//                              std::numeric_limits<Type>::lowest());
//}
//
//
//template <typename Type>
//void Parameter<Type>::makeReferenceTo(ofParameter<Type>& parameter)
//{
//    // 1. Remove the reference to the internal parameter.
//    _parameter.removeListener(this, &Parameter<Type>::_onParameterChanged,
//                              std::numeric_limits<Type>::lowest());
//    // 2. Make the internal parameter a refefence to the external parameter.
//    _parameter.makeReferenceTo(parameter);
//    // 3. Make this instance a listener to the external parameter.
//    _parameter.addListener(this, &Parameter<Type>::_onParameterChanged,
//                           std::numeric_limits<Type>::lowest());
//}
//
//
//template <typename Type>
//Type Parameter<Type>::operator=(Type v)
//{
//    _parameter = v;
//    return v;
//}
//
//template <typename Type>
//Parameter<Type>::operator const Type& ()
//{
//    return _parameter;
//}
//
//
////template <typename Type>
////void Parameter<Type>::_onParameterChanged(const void* sender, Type& value)
////{
////    // We forward the event changes as sent by the slider.
////    ofNotifyEvent(onParameterChanged, value, this);
////}
//
//
//
//} } // ofx::MUI
