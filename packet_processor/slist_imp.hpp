/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once


#include <sstream>
#include <stdexcept>
#include <cassert>

#include "slist.hpp"

template <class T>
SNode<T>::SNode (T const& it)
{
    //DONE
    _item=it;
    _next=nullptr;
    //
    assert(!has_next());
}

template <class T>
SNode<T>::SNode (T const& it, SNode<T>::Ref& next)
{
    //DONE
    _item=it;
    _next=next;
    //
}

template <class T>
SNode<T>::~SNode()
{
    //DONE
    //hint: if std::shared_ptr is used for the references, nothing todo.
    //NOTHING
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
    //DONE
    it=_item;
    //
    return it;
}

template <class T>
bool SNode<T>::has_next() const
{
    bool has = false;
    //DONE
    has=(_next!=nullptr);
    //
    return has;
}

template <class T>
typename SNode<T>::Ref SNode<T>::next() const
{
    SNode<T>::Ref n;
    //DONE
    n=_next;
    //
    return n;
}

template <class T>
void SNode<T>::set_item(const T& new_it)
{
    //DONE
    _item=new_it;
    //
    assert(item()==new_it);
}

template <class T>
void SNode<T>::set_next(SNode<T>::Ref n)
{
    //DONE
    _next=n;
    //
    assert(n == next());
}

template<class T>
SList<T>::SList ()
{
    //DONE
    _head=nullptr;
    _size=0;
    _prev=nullptr;
    _curr=nullptr;
    //
    assert(is_empty());
}

template<class T>
SList<T>::~SList()
{
    //DONE

    //NOTHING

    //

}

template<class T>
typename SNode<T>::Ref SList<T>::head() const
{
    typename SNode<T>::Ref h;
    //DONE
    h=_head;
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

    //DONE
    //Hint: use std::istringstream to convert from "string" to template
    // parameter T type.
    // Throw std::runtime_error("Wrong input format.") exception when an input
    // format error was found.
    T elem_T;

    if(token=="[]") return list;    //Si esta vacia la devuelve directamente

    //Comprueba que se cumple el formato
    if(token!="[") throw std::runtime_error("Wrong input format.");

    while(in>>token && token!="]"){

        std::istringstream elem(token);
        elem >> elem_T;
        if(elem.fail()) throw std::runtime_error("Wrong input format.");

        list->insert(elem_T);
        if(list->has_next()) list->goto_next();
    }

    //Comprueba que se cumple el formato (si acaba y el ult token no es ],
    //es que no esta bien cerrada)
    if(token!="]") throw std::runtime_error("Wrong input format.");

    //
    return list;
}

template<class T>
bool SList<T>::is_empty () const
{
    bool ret_val = true;
    //DONE
    ret_val=(_size==0);
    //
    return ret_val;
}

template<class T>
size_t SList<T>::size () const
{
    size_t ret_val = 0;
    //DONE
    ret_val=_size;
    //
    return ret_val;
}

template<class T>
T SList<T>::front() const
{
    assert(!is_empty());
    T f;
    //DONE
    f=_head->item();
    //
    return f;
}

template<class T>
T SList<T>::current() const
{    
    assert(! is_empty());
    T c;
    //DONE
    c=_curr->item();
    //
    return c;
}

template<class T>
bool SList<T>::has_next() const
{
    assert(!is_empty());
    bool ret_val = false;
    //DONE
    ret_val=(_curr->next()!=nullptr);
    //
    return ret_val;
}

template<class T>
T SList<T>::next() const
{
    assert(has_next());
    T ret_val = false;
    //DONE
    ret_val=_curr->next()->item();
    //
    return ret_val;
}


template<class T>
bool SList<T>::has(T const& it) const
{
    bool found = false;
    //DONE
    //Hint: you can reuse SList::find() but you must remember to restore 
    // the old the cursor position. In this way we assure not modify the state of the list.
    //Hint: use const_cast<> to remove constness of this.
    std::shared_ptr<SNode<T>> auxprev=_prev;
    std::shared_ptr<SNode<T>> auxcurr=_curr;
    
    found = (const_cast<SList<T>*>(this))->find(it);

    (const_cast<SList<T>*>(this))->_prev=auxprev;
    (const_cast<SList<T>*>(this))->_curr=auxcurr;
    //
    return found;
}

template<class T>
void SList<T>::fold(std::ostream& out) const
{
    //DONE
    typename SNode<T>::Ref elem = _head;

    out<<"[";

    if(is_empty()){
        out<<"]";
        return;
    }

    while(elem!=nullptr){
        out<<" "<<elem->item();
        elem=elem->next();
    }
    out<<" "<<"]";
    //
}

template<class T>
void SList<T>::set_current(T const& new_v)
{
    assert(!is_empty());
    //DONE
    _curr->set_item(new_v);
    //
    assert(current()==new_v);
}


template<class T>
void SList<T>::push_front(T const& new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    //DONE
    //Remeber to update current if current is in the head.
    std::shared_ptr<SNode<T>> new_node = SNode<T>::create(new_it, _head);

    if(_curr==_head) _curr=new_node;

    _head=new_node;
    _size++;
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
    //DONE
    if(is_empty()){ 
        push_front(new_it);
    }
    else{
        std::shared_ptr<SNode<T>> new_node = SNode<T>::create(new_it, _curr->next());
        _curr->set_next(new_node);
        _size++;
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
    if(_curr==_head){
        _curr=_curr->next();
    }

    _head=_head->next();
    _size--;
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
    //DONE
    //Case 1: current is the head.
    if(_curr==_head) pop_front();
    //Case 2: remove in a middle position.
    else if(_curr->has_next()){
        _prev->set_next(_curr->next());
        _curr=_curr->next();
        _size--;
    }
    //Case 3: remove the last element.
    //Remenber to locate previous of prev_.
    else{
        _curr=_prev;
        _curr->set_next(nullptr);
        _size--;
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
    //DONE
    _prev=_curr;
    _curr=_curr->next();
    //
    assert(current()==old_next);
}

template<class T>
void SList<T>::goto_first()
{
    assert(!is_empty());
    //DONE
    _curr=_head;
    //
    assert(current()==front());
}

template<class T>
bool SList<T>::find(T const& it)
{
    assert(!is_empty());
    bool found = false;
    //DONE
    goto_first();
    if(_curr->item()==it) return true;

    while(_curr->has_next()){
        goto_next();
        if(_curr->item()==it) return true;
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
    //DONE
    while(_curr->has_next()){
        goto_next();
        if(_curr->item()==it) return true;
    }
    //
    assert(!found || current()==it);
    assert(found || !has_next());
    return found;
}

