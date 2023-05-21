/**
 * @file graph_utils_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <string>

#include "wgraph.hpp"

/** GraphNode implementation **/

template<class T>
WNode<T>::WNode(size_t label, T const& v)
{
    //DONE
    label_=label;
    item_=v;
    //
    assert(item()==v);
    assert(!is_visited());
}

template<class T>
T WNode<T>::item() const
{
    T ret_v;
    //DONE
    ret_v=item_;
    //
    return ret_v;
}

template<class T>
size_t  WNode<T>::label() const
{
    size_t ret_v = 0;
    //DONE
    ret_v=label_;
    //
    return ret_v;
}

template<class T>
bool  WNode<T>::is_visited() const
{
    bool ret_v = false;
    //DONE
    ret_v=visited_;
    //
    return ret_v;
}

template<class T>
void WNode<T>::set_item(T const& v)
{
    //DONE
    item_=v;
    //
    assert(item()==v);
}


template<class T>
void WNode<T>::set_visited(bool new_st)
{
    //DONE
    visited_=new_st;
    //
    assert(new_st || !is_visited());
    assert(!new_st || is_visited());
}

/** GraphEdge implementation **/

template<class T, class E>
WEdge<T,E>::WEdge(NodeRef u, NodeRef v, FMatrix::Ref wmat)
{
    //DONE
    u_=u;
    v_=v;
    wmat_=wmat;
    //
}

template<class T, class E>
E WEdge<T,E>::weight() const
{
    E ret_val=std::numeric_limits<float>::infinity();
    //DONE
    ret_val=wmat_->get(u_->label(), v_->label());
    //
    return ret_val;
}

template<class T, class E>
bool WEdge<T,E>::has(NodeRef const& n) const
{
    bool ret_val = false;
    //DONE
    ret_val=(u_==n || v_==n);
    //
    return ret_val;
}

template<class T, class E>
typename WEdge<T,E>::NodeRef WEdge<T,E>::other(NodeRef const& n) const
{
    assert(has(n));
    NodeRef ret_val;
    //DONE
    if(u_==n) ret_val=v_;
    else ret_val=u_;
    //
    return ret_val;
}

template<class T, class E>
typename WEdge<T,E>::NodeRef WEdge<T,E>::first() const
{
    NodeRef ret_val;
    //DONE
    ret_val=u_;
    //
    return ret_val;
}

template<class T, class E>
typename WEdge<T,E>::NodeRef WEdge<T,E>::second() const
{
    NodeRef ret_val;
    //DONE
    ret_val=v_;
    //
    return ret_val;
}

template<class T, class E>
void WEdge<T,E>::set_weight(E const& v)
{
    //DONE
    wmat_->set(u_->label(), v_->label());
    //
    assert(weight()==v);
}


/** WGraph implementation **/
template<class T>
WGraph<T>::WGraph (size_t capacity, float default_weight)
{
    assert(capacity>0);

    //DONE
    //Remember: this a weighted graph, so all the nodes are connected with
    //          infinite weight by default.
    capacity_=capacity;
    wmat_= FMatrix::create(capacity, capacity, default_weight);
    //

    assert(is_empty());
    assert(!has_current_node());
    assert(!has_current_edge());
}

template<class T>
bool WGraph<T>::is_empty() const
{
    bool ret_v = true;
    //DONE
    ret_v=nodes_.empty();
    //
    assert(!ret_v || size()==0);
    return ret_v;
}

template<class T>
bool WGraph<T>::is_full() const
{
    bool ret_v = true;
    //DONE
    ret_v=(size()==capacity());
    //
    assert(!ret_v || size()==capacity());
    return ret_v;
}

template<class T>
size_t WGraph<T>::size() const
{
    size_t ret_v = 0;
    //DONE
    ret_v=nodes_.size();
    //
    return ret_v;
}

template<class T>
size_t WGraph<T>::capacity() const
{
    size_t ret_v = 0;
    //DONE
    ret_v=capacity_;
    //
    return ret_v;
}

template<class T>
bool WGraph<T>::has(NodeRef u) const
{
    assert (u != nullptr);
    bool ret_v = true;
    //DONE
    ret_v=( std::find(nodes_.begin(), nodes_.end(), u) != nodes_.end() );
    //
    assert(!ret_v || (u->label()<capacity() && node(u->label())==u));
    return ret_v;
}

template<class T>
bool WGraph<T>::are_adjacent (NodeRef u, NodeRef v) const
{
    assert( has(u) && has(v) );
    bool ret_v = false;
    //DONE
    //Remember: this a Weighted graph so a node u is adjacent to v if the
    //          edge's weight is less than infinite.
    // Hint: use std::numeric_limits<float> facet to get infinite as float value.
    float inf = std::numeric_limits<T>::infinity();
    ret_v=(wmat_->get(u->label(), v->label()) != inf);
    //
    return ret_v;
}

template<class T>
bool WGraph<T>::has_current_node () const
{
    bool ret_v = false;
    //DONE
    //Hint: use attribute _size to mark "end".
    ret_v=(curr_>=0 && curr_<size());
    //
    return ret_v;
}

template<class T>
typename WGraph<T>::NodeRef WGraph<T>::current_node () const
{
    assert(has_current_node());
    NodeRef ret_v;
    //DONE
    ret_v=nodes_[curr_];
    //
    return ret_v;
}

template<class T>
bool WGraph<T>::has_current_edge () const
{
    bool ret_v = false;    
    //DONE
    //Remember: first it must exist a current node.
    //Hint: use value size() to mark "end".
    if(!has_current_node()) return ret_v;
    if(curr_edge_>=0 && curr_edge_<size()) ret_v=true;
    //
    assert(!ret_v || has_current_node());
    return ret_v;
}

template<class T>
float WGraph<T>::current_weight () const
{
    assert(has_current_edge());
    float ret_v = 0.0;
    //DONE
    ret_v=wmat_->get(curr_, curr_edge_);
    //
    assert(ret_v<std::numeric_limits<float>::infinity());
    return ret_v;
}

template<class T>
FMatrix::Ref WGraph<T>::weight_matrix() const
{
    FMatrix::Ref mat;
    //DONE
    mat=wmat_;
    //
    return mat;
}

template<class T>
float WGraph<T>::weight(size_t u_label, size_t v_label) const
{
    assert(u_label<size());
    assert(v_label<size());
    float ret_v = 0.0;
    //DONE
    ret_v=wmat_->get(u_label, v_label);
    //
    assert(ret_v == weight(node(u_label), node(v_label)));
    return ret_v;
}

template<class T>
float WGraph<T>::weight (NodeRef u, NodeRef v) const
{
    assert(has(u));
    assert(has(v));
    float ret_v = 0.0;
    //DONE
    ret_v=wmat_->get(u->label(), v->label());
    //
    return ret_v;
}

template<class T>
typename WGraph<T>::EdgeRef WGraph<T>::edge(NodeRef u, NodeRef v) const
{
    assert(has(u));
    assert(has(v));
    EdgeRef ret_v=nullptr;
    //DONE
    ret_v=WEdge<T,float>::create(u, v, weight_matrix());
    //
    assert(ret_v->first()==u);
    assert(ret_v->second()==v);
    assert(ret_v->weight()==weight(u, v));
    return ret_v;
}

template<class T>
typename WGraph<T>::EdgeRef WGraph<T>::edge(size_t u_label, size_t v_label) const
{
    assert(u_label<size());
    assert(v_label<size());
    EdgeRef ret_v=nullptr;
    //DONE
    //Hint: use the static method WEdge::create().
    ret_v=WEdge<T,float>::create(nodes_[u_label], nodes_[v_label], weight_matrix());
    //
    assert(ret_v->first()->label()==u_label);
    assert(ret_v->second()->label()==v_label);
    assert(ret_v->weight()==weight(u_label, v_label));
    return ret_v;
}

template<class T>
typename WGraph<T>::EdgeRef WGraph<T>::current_edge() const
{
    assert(has_current_edge());
    EdgeRef ret_v = nullptr;
    //DONE
    //Hint: use the static method WEdge::create().
    ret_v=WEdge<T,float>::create(nodes_[curr_], nodes_[curr_edge_], weight_matrix());
    //
    assert(ret_v->first()==current_node() && ret_v->weight()<std::numeric_limits<float>::infinity());
    return ret_v;
}

template<class T>
typename WGraph<T>::NodeRef WGraph<T>::node(size_t label) const
{
    assert(label<size());
    NodeRef n;
    //DONE
    n=nodes_[label];
    //
    return n;
}

template<class T>
void WGraph<T>::set_visited(bool state)
{
    //DONE
    // Remember: we only have visited flag in nodes, no one in edges.
    nodes_[curr_]->set_visited(state);
    //
}

template<class T>
void WGraph<T>::goto_first_node()
{
    assert(!is_empty());
    //DONE
    //Remember: the edge's cursor must be initialized too.
    curr_=0;
    while(!has_current_node()){
        curr_++;
    }

    curr_edge_=0;

    while(!(wmat_->get(curr_, curr_edge_) < std::numeric_limits<float>::infinity())){
        
        if(curr_edge_>size()) break;
        curr_edge_++;
    }
    //
    assert(!has_current_edge()||current_edge()->first() == current_node());
    assert(!has_current_edge() ||
           current_weight()<std::numeric_limits<float>::infinity());
}

template<class T>
void WGraph<T>::goto_first_edge()
{
    assert(has_current_node());
    //DONE
    // Remember: we consider here edges with weight < infinite.
    float inf = std::numeric_limits<float>::infinity();
    curr_edge_=0;

    while(!(wmat_->get(curr_, curr_edge_)<inf)){

        if(curr_edge_>size()) break;
        curr_edge_++;
    }
    //
    assert(!has_current_edge()||current_edge()->first() == current_node());
    assert(!has_current_edge() ||
           current_weight()<std::numeric_limits<float>::infinity());
}

template<class T>
void WGraph<T>::goto_next_node()
{
    assert(has_current_node());
    //DONE
    // Remember: you must update the edge cursor too.
    curr_++;
    if(has_current_node()) goto_first_edge();
    else curr_edge_=-1;
    //
    assert(has_current_node() || !has_current_edge());
    assert(!has_current_edge() || (current_edge()->first() == current_node()));
    assert(!has_current_edge() ||
           current_weight()<std::numeric_limits<float>::infinity());
}

template<class T>
void WGraph<T>::goto_next_edge()
{
    assert(has_current_edge());
    //DONE
    // Remember: we consider here edges with weight < infinite.
    curr_edge_++;

    while(!(wmat_->get(curr_, curr_edge_)<std::numeric_limits<float>::infinity())){
        
        if(curr_edge_>size()) break;
        curr_edge_++;
    }
    //
    assert(!has_current_edge() || current_edge()->first() == current_node());
    assert(!has_current_edge() ||
           current_weight()<std::numeric_limits<float>::infinity());
}

template<class T>
void WGraph<T>::goto_node(NodeRef u)
{
    assert(has(u));
    //DONE
    // Remember: update edge cursor too.
    curr_=u->label();
    goto_first_edge();
    //
    assert(!has_current_edge() || current_edge()->first()==u);
    assert(!has_current_edge() ||
           current_weight()<std::numeric_limits<float>::infinity());
}

template<class T>
void WGraph<T>::goto_edge(NodeRef u, NodeRef v)
{
    assert(has(u));
    assert(has(v));
    assert(weight(u, v) < std::numeric_limits<float>::infinity());
    //DONE
    //Remember: node and edge cursors must be initialized too.
    curr_=u->label();
    curr_edge_=wmat_->get(u->label(), v->label());
    //
    assert(current_node()==u);
    assert(current_edge()->first()==u);
    assert(current_edge()->second()==v);
    assert(current_weight()==weight(u,v));
}

template<class T>
void WGraph<T>::goto_edge(EdgeRef e)
{
    assert(has(e->first()));
    assert(has(e->second()));
    assert(e->weight() < std::numeric_limits<float>::infinity());
    //DONE
    //Remember: node and edge cursors must be initialized too.
    curr_=e->first();
    curr_edge_=e->second();
    //
    assert(current_node()==e->first());
    assert(current_edge()->second()==e->second());
    assert(current_weight()==e->weight());
}

template<class T>
typename WGraph<T>::NodeRef WGraph<T>::find_node(typename T::key_t const& key)
{
    assert(!is_empty());
    NodeRef ret_v = nullptr;
    //DONE
    // Remember: update node and edge cursors.
    // Remember: The item.key() is used to look for.
    goto_first_node();
    while(curr_<size()){
        if(nodes_[curr_]->item()==key){
            ret_v=nodes_[curr_];
            break;
        }
        goto_next_node();
    }
    //
    assert((ret_v==nullptr) || (has_current_node() && current_node()==ret_v));
    assert(!has_current_node() || current_node()->item()==key);
    assert(!has_current_edge() || current_edge()->first()==current_node());
    return ret_v;
}

template<class T>
typename WGraph<T>::NodeRef WGraph<T>::find_next_node(typename T::key_t const& key)
{
    assert(!is_empty());
    NodeRef ret_v = nullptr;
    //DONE
    // Remember: update node and edge cursors.
    // Remember: The item.key() is used to look for.
    find_node(key);
    goto_next_node();
    //
    assert((ret_v==nullptr) || (has_current_node() && current_node()==ret_v));
    assert(!has_current_node() || current_node()->item()==key);
    assert(!has_current_edge() || current_edge()->first()==current_node());
    return ret_v;
}

template<class T>
void WGraph<T>::set_current_weight(float new_w)
{
    assert(has_current_edge());
    //DONE
    // Remember: set infinite as new weight invalidates edge_cursor.
    wmat_->set(curr_, curr_edge_, new_w);
    //
    assert(new_w < std::numeric_limits<float>::infinity() || !has_current_edge());
}

template<class T>
void WGraph<T>::set_weight(size_t u_label, size_t v_label, float new_w)
{
    assert(u_label<size());
    assert(v_label<size());
    // DONE
    // Remember: set infinite as new weight could invalidate the edge cursor if it is currently points to this edge.
    if(new_w==std::numeric_limits<float>::infinity()){
        curr_=nullptr;
        curr_edge_=nullptr;
    }
    wmat_->set(u_label, v_label, new_w);
    //
    assert(new_w == weight(u_label, v_label));
    assert(!has_current_edge() || current_weight()<std::numeric_limits<float>::infinity());
}

template<class T>
void WGraph<T>::set_weight(NodeRef u, NodeRef v, float new_w)
{
    assert(has(u));
    assert(has(v));
    //DONE
    // Remember: set infinite as new weight could invalidate the edge cursor if it is currently points to this edge.
    wmat_->set(u->label(), v->label(), new_w);
    //
    assert(weight(u, v)==new_w);
    assert(!has_current_edge() || current_weight()<std::numeric_limits<float>::infinity());
}

template<class T>
void WGraph<T>::add_node(T const& v)
{
    assert(! is_full());
    //DONE
    // Remember: update node and edge cursors.
    NodeRef node = WNode<T>::create(nodes_.size() ,v);
    nodes_.push_back(node);
    curr_edge_=-1;
    //
    assert(has_current_node());
    assert(!has_current_edge());
}

template <class T>
std::ostream&
WGraph<T>::fold(std::ostream& out) const
{
    //DONE
    //Hint: the Matrix template has a fold method.
    //'[ '<capacity>' '<size>{' '<node_item>}*' wmat_->fold() ]'
    
    out<<"[ "<<capacity_<<" "<<size()<<" ";

    for(auto it=nodes_.begin(); it != nodes_.end(); it++){

        out<<(*it)->item()<<" ";
    }

    wmat_->fold(out);
    out<<" ]";
    //
    return out;
}

template <class T>
WGraph<T>::WGraph (std::istream& input) noexcept(false)
{
    //DONE
    //Remember: capacity is the max number of nodes that the graph could have.
    //          size is the current number of nodes (size <= capacity).
    //Hint: The Matrix template has a unfold method.

    std::string token;
    input>>token;
    if(token!="[") throw std::runtime_error("Wrong input format.");

    input>>capacity_;
    //std::cout<<capacity_<<std::endl; //debug

    int size;
    input>>size;
    //std::cout<<size<<std::endl; //debug

    T item;
    for(int i=0; i<size; i++){
        input>>item;
        //std::cout<<item<<std::endl; //debug
        add_node(item);
    }
    curr_=-1;
    curr_edge_=-1;

    wmat_= FMatrix::create(input);
    //
    assert(!has_current_node());
    assert(!has_current_edge());
}

template <class T>
typename WGraph<T>::Ref WGraph<T>::create (std::istream & input)
{
    return std::make_shared<WGraph<T>>(input);

}

template<class T>
typename WGraph<T>::Ref create_wgraph(std::istream &in) noexcept(false)
{
    assert(in);
    typename WGraph<T>::Ref graph = nullptr; //The returned graph.

    //DONE    
    //Remember: Throw std::runtime_error("Wrong graph") when detecting a wrong
    // input format.
    //Remember: key_t type is used to give the edge's ends.
    std::string token;

    //DONE
    //First: Determine if it is directed or undirected.
    in.get();
    getline(in, token);
    std::string dir = token;
    //

    //DONE
    //Second: get the number of nodes and create a wgraph with this capacity.
    getline(in, token);
    size_t capacity = std::stoi(token);
    graph = WGraph<T>::create(capacity); 
    //

    //DONE
    //Third: load the N T data items and adding the nodes.
    T item;

    for(size_t i = 0; i < capacity; i++){
        getline(in, token);
        std::istringstream convert(token);
        convert >> item;
        graph->add_node(item);
    }
    //

    //DONE
    //Fourth: load the number of edges.
    getline(in, token);
    size_t nEdges = std::stoi(token);
    //

    //DONE
    //Fifth: load the N edges.
    //Remember: Use T::key_t type to load the edge's ends.
    //Remember: if the input graph is UNDIRECTED we simulated this with a WGraph
    // duplicating each input edge (u,v) making too the (v,u) edge with same weight
    // with the same weight.
    if(dir == "DIRECTED"){
        for(size_t i = 0; i < nEdges; i++){
            T item;
            typename WNode<T>::Ref u;
            typename WNode<T>::Ref v;
            size_t weight;

            in >> token;
            
            std::istringstream convert(token);
            
            convert >> item;
            u = graph->find_node(item.key());

            in >> token;

            std::istringstream convert2(token);

            convert2 >> item;
            v = graph->find_node(item.key());

            in >>token;
            
            weight = std::stoi(token);

            graph->set_weight(u, v, weight);
        }
    } else if(dir == "UNDIRECTED"){
        for(size_t i = 0; i < nEdges; i++){
            typename T::key_t item;
            typename WNode<T>::Ref u;
            typename WNode<T>::Ref v;
            size_t weight;

            in >> token;
            
            std::istringstream convert(token);
            
            convert >> item;
            u = graph->find_node(item);

            in >> token;

            std::istringstream convert2(token);

            convert2 >> item;
            v = graph->find_node(item);

            in >>token;
            
            weight = std::stoi(token);

            graph->set_weight(u, v, weight);
            graph->set_weight(v, u, weight);        
        }
    }

    //

    return graph;
}

