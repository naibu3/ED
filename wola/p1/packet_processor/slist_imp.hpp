/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include "slist.hpp"
#include <sstream>
#include <stdexcept>
#include <cassert>

template <class T>
SNode<T>::SNode (T const& it)
{
    //TODO
    _item=it;
    _next=nullptr;
    //
    assert(!has_next());
}

template <class T>
SNode<T>::SNode (T const& it, SNode<T>::Ref& next)
{
    //TODO
    _item=it;
    _next=next;
    //
}

template <class T>
SNode<T>::~SNode()
{
    //TODO
    //hint: if std::shared_ptr is used for the references, nothing todo.
    //
}

template <class T>
typename SNode<T>::Ref SNode<T>::create(T const& it, SNode<T>::Ref next)
{
    return std::make_shared<SNode<T>> (it, next);
}

template <class T>
T SNode<T>::item() const
{
    T it;
    //TODO
    it=_item;
    //
    return it;
}

template <class T>
bool SNode<T>::has_next() const
{
    bool has = false;
    //TODO
    has= _next!=nullptr;
    //
    return has;
}

template <class T>
typename SNode<T>::Ref SNode<T>::next() const
{
    SNode<T>::Ref n;
    //TODO
    n=_next;
    //
    return n;
}

template <class T>
void SNode<T>::set_item(const T& new_it)
{
    //TODO
    _item=new_it;
    //
    assert(item()==new_it);
}

template <class T>
void SNode<T>::set_next(SNode<T>::Ref n)
{
    //TODO
    _next=n;
    //
    assert(n == next());
}

template<class T>
SList<T>::SList ()
{
    //TODO
    _cabeza=nullptr;
    _actual=nullptr;
    _anterior=nullptr;
    //
    assert(is_empty());
}

template<class T>
SList<T>::~SList()
{
    //TODO

    //
}

template<class T>
typename SNode<T>::Ref SList<T>::head() const
{
    typename SNode<T>::Ref h;
    //TODO
    h=_cabeza;
    //
    return h;
}
template<class T>
typename SNode<T>::Ref SList<T>::curr() const
{
    typename SNode<T>::Ref h;
    //TODO
    h=_actual;
    //
    return h;
}

template<class T>
typename SList<T>::Ref SList<T>::create()
{
    return std::make_shared<SList<T>> ();
}

template<class T>
typename SList<T>::Ref SList<T>::create(std::istream& in) noexcept(false)
{
    auto list = SList<T>::create();
    std::string token;
    in >> token;

    //TODO
    //Hint: use std::istriongstream to convert from "string" to template
    // parameter T type.
    // Throw std::runtime_error("Wrong input format.") exception if a input
    // format error was found.
    T num;

    if(token=="[]")     //lista vacía
        return list;

    if(token!="["){     //entrada de lista
        throw std::runtime_error("Wrong input format.");
    }
    while(in>>token && token!="]"){     //mientras quede por procesar
        std::istringstream my_stream(token);
        my_stream>>num;                 //de string a T
        if(my_stream.fail()){           // si no es T  
            throw std::runtime_error("Wrong input format.");
        }
        list->insert(num);
        if(list->has_next()){
            list->goto_next();
        }
    }
    if(token != "]"){                   //cierre de lista
        throw std::runtime_error("Wrong input format.");
    }
    //
    return list;
}

template<class T>
bool SList<T>::is_empty () const
{
    bool ret_val = true;
    //TODO
    ret_val= _cabeza==nullptr;
    //
    return ret_val;
}

template<class T>
size_t SList<T>::size () const
{
    size_t ret_val = 0;
    //TODO
    ret_val=_tam;
    //
    return ret_val;
}

template<class T>
T SList<T>::front() const
{
    assert(!is_empty());
    T f;
    //TODO
    f=_cabeza->item();
    //
    return f;
}

template<class T>
T SList<T>::current() const
{    
    assert(! is_empty());
    T c;
    //TODO
    c=curr()->item(); 
    //
    return c;
}

template<class T>
bool SList<T>::has_next() const
{
    assert(!is_empty());
    bool ret_val = false;
    //TODO
    ret_val=curr()->next()!=nullptr;
    //
    return ret_val;
}

template<class T>
T SList<T>::next() const
{
    assert(has_next());
    T ret_val = false;
    //TODO
    ret_val=_actual->next()->item();
    //
    return ret_val;
}


template<class T>
bool SList<T>::has(T const& it) const
{
    bool found = false;
    //TODO
    //Hint: you can reuse SList::find() but remebering restore cursors to
    //assure not modify the state of the list.
    //Hint: use const_cast<> to remove constness of this.
    
    std::shared_ptr<SNode<T>> oldActual=_actual;
    std::shared_ptr<SNode<T>> oldAnterior=_anterior;

    found=(const_cast<SList<T>*>(this))->find(it);
    
    (const_cast<SList<T>*>(this))->_actual=oldActual;
    (const_cast<SList<T>*>(this))->_anterior=oldAnterior;
    //
    return found;
}

template<class T>
void SList<T>::fold(std::ostream& out) const
{
    //TODO
    typename SNode<T>::Ref i = _cabeza;
    out << "[";
    if(!is_empty()){
        while (i!=nullptr){
            out << " " << i->item();
            i=i->next();
        }
      }
    out <<" "<< "]";
    //
}


template<class T>
void SList<T>::set_current(T const& new_v)
{
    assert(!is_empty());
    //TODO
    _actual->set_item(new_v);
    //
    assert(current()==new_v);
}


template<class T>
void SList<T>::push_front(T const& new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    //TODO
    //Remeber to update current if current is in the head.
     std::shared_ptr< SNode<T>> new_node = SNode<T>::create(new_it, _cabeza);
      if(_actual == _cabeza){
          _actual = new_node;
      }
      _cabeza = new_node;
      _tam++;
    //
    assert(front()==new_it);
    assert(size() == (old_size+1));
}

template<class T>
void SList<T>::insert(T const& new_it)
{
#ifndef NDEBUG
    bool old_is_empty = is_empty();
    size_t old_size = size();
    T old_item;
    if (!old_is_empty)
        old_item = current();
#endif
    //TODO
    if(is_empty()){
        push_front(new_it);
    }
    else{
        std::shared_ptr< SNode<T>> new_node = SNode<T>::create(new_it, _actual->next());
        _actual->set_next(new_node);
        _tam++;
    }

    //
    assert(!old_is_empty || (front()==new_it && current()==new_it));
    assert(old_is_empty || (old_item == current() && has_next() && next()==new_it));
    assert(size()==(old_size+1));
}

template<class T>
void SList<T>::pop_front()
{
    assert(!is_empty());
#ifndef NDEBUG
    size_t old_size = size();
    auto old_head_next = head()->next();
#endif
    //DONE
    if(_actual==_cabeza){
        _actual=_actual->next();
    }
    _cabeza=_cabeza->next();
    _tam--;
    //
    assert(is_empty() || head() == old_head_next);
    assert(size() == (old_size-1));
}


template<class T>
void SList<T>::remove()
{
    assert(!is_empty());
#ifndef NDEBUG
    size_t old_size = size();
    bool old_has_next = has_next();
    T old_next;
    if (has_next())
        old_next=next();
#endif
    //TODO
    //Case 1: current is the head.

    //Case 2: remove in a middle position.

    //Case 3: remove the last element.
    //Remenber to locate previous of prev_.
    if(_actual==_cabeza){
        pop_front();
    }
    else if(_actual->has_next()){
        _anterior->set_next(_actual->next());
        _actual=_actual->next();
        _tam--;
    }
    else{
        goto_first();
        while(_actual->next()->has_next()){
            goto_next();
        }
        _actual->set_next(nullptr);
        _tam--;
    }
    //
    assert(!old_has_next || current()==old_next);
    assert(size() == (old_size-1));
}

template<class T>
void SList<T>::goto_next()
{
    assert(has_next());
#ifndef NDEBUG
    auto old_next = next();
#endif
    //TODO
    _anterior=_actual;
    _actual=_actual->next();
    //
    assert(current()==old_next);
}

template<class T>
void SList<T>::goto_first()
{
    assert(!is_empty());
    //TODO
    _actual=_cabeza;
    //
    assert(current()==front());
}

template<class T>
bool SList<T>::find(T const& it)
{
    assert(!is_empty());
    bool found = false;
    //TODO
    goto_first();
    if(_actual->item()==it){
            return true;
    }
    while(_actual->has_next()){
        goto_next();
        if(_actual->item()==it){
            return true;
        }
    }
    //
    assert(!found || current()==it);
    assert(found || !has_next());
    return found;
}

template<class T>
bool SList<T>::find_next(T const& it)
{
    assert(has_next());
    bool found = false;
    //TODO
    while(_actual->has_next()){
        goto_next();
        if(_actual->item()==it){
            return true;
        }
    }
    //
    assert(!found || current()==it);
    assert(found || !has_next());
    return found;
}

