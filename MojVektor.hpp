#pragma once
#include <initializer_list>
#include <iterator>

template <typename T>
class MojVektor {
  public:
  class Iterator;
  
  MojVektor();
  MojVektor(const std::initializer_list<T>&);
  MojVektor(const MojVektor&);
  MojVektor& operator=(const MojVektor&);
  MojVektor(MojVektor&&);
  MojVektor& operator=(MojVektor&&);
  ~MojVektor();

  MojVektor& push_back(const T&);
  MojVektor& push_front(const T&);
  MojVektor& push_back(T&&);
  MojVektor& push_front(T&&);
  size_t size() const;
  T& at(size_t) const;
  T& operator[](size_t) const;

  void clear();
  void resize(size_t newSize, const T& difference_value);
  MojVektor& pop_back();
  MojVektor& pop_front();
  T& back() const;
  T& front() const;

  bool empty() const;
  size_t capacity() const;

  bool operator==(const MojVektor&) const;
  bool operator!=(const MojVektor&) const;
  bool full() const;

  MojVektor subvector(Iterator begin, Iterator end);
  Iterator begin() const;
  Iterator end() const;
  Iterator find(const T&) const;
  Iterator erase(Iterator pos);
  Iterator insert(Iterator, const T&);
  Iterator insert(Iterator, T&&);
  Iterator rbegin() const;
  Iterator rend() const;
  Iterator erase(Iterator beginIt, Iterator endIt);
  void rotate();
  void rotate(Iterator beginIt, Iterator endIt);

  T* data();
  
friend std::ostream& operator<<(std::ostream& out, const MojVektor<T>& o){
out << "{";
for(int i=0; i<o.size(); i++){
out<<o.arr_[i];
if(i != o.size()-1){
out<<", ";
};
};
out<< "}";
return out;
};

  private:
  void realoc();
  size_t capacity_;
  size_t size_;
  T* arr_;
};

// Implementacija ovdje
template <typename T>
void MojVektor<T>::realoc(){
capacity_*=2;
auto tmp = new T [capacity_];
std::copy(arr_, arr_+size_, tmp);
delete [] arr_;
arr_ = tmp;
};

template <typename T>
MojVektor<T>::MojVektor()
: capacity_{10}, size_{0}, arr_{new T [capacity_]}
{};

template <typename T>
MojVektor<T>::MojVektor(const std::initializer_list<T>& il)
: capacity_{il.size()}, size_ {capacity_}, arr_{new T [capacity_]}
{
  std::copy(il.begin(), il.end(), arr_); 
};

template <typename T>
MojVektor<T>::MojVektor(const MojVektor& other)
: capacity_{other.capacity_}, size_{other.size_}, arr_{new T [capacity_]}
{
  std::copy(other.arr_, other.arr_+other.size_, arr_); 
};

template <typename T>
MojVektor<T>& MojVektor<T>::operator=(const MojVektor& other){
delete [] arr_;
capacity_ = other.capacity_;
size_= other.size_;
arr_ = new T [capacity_];

std::copy(other.arr_, other.arr_+other.size_, arr_); 

return *this;
};

template <typename T>
MojVektor<T>::MojVektor(MojVektor&& other)
: capacity_{other.capacity_}, size_{other.size_}, arr_{other.arr_}
{
other.arr_ = nullptr;
other.capacity_ = other.size_ = 0;
};

template <typename T>
MojVektor<T>&  MojVektor<T>::operator=(MojVektor&& other){

delete [] arr_;

capacity_ = other.capacity_;
size_ = other.size_;
arr_ = other.arr_;

other.capacity_ = other.size_ = 0;
other.arr_=nullptr;
return *this;
};

template <typename T>
MojVektor<T>::~MojVektor(){
delete [] arr_;
capacity_ = size_ = 0;
arr_ = nullptr;
};

template <typename T>
T& MojVektor<T>::at(size_t element) const{
if (element > size_) throw std::out_of_range{"Indeks van granica!"};
return arr_[element];
};

template <typename T>
 T& MojVektor<T>::operator[](size_t element) const{
return arr_[element];
 };

template <typename T>
 size_t MojVektor<T>::size() const{
 return size_;
 };

template <typename T>
  bool  MojVektor<T>::empty() const{
  return size_ == 0;
  };

template <typename T>
  size_t MojVektor<T>::capacity() const{
  return capacity_;
  };

template <typename T>
MojVektor<T>&  MojVektor<T>::push_back(const T& o){
if(size_ == capacity_){
  realoc();
};
arr_ [size_++] = o;
return *this;
};
 
template <typename T>
MojVektor<T>& MojVektor<T>::push_front(const T& o){
if(size_ == capacity_){
capacity_*=2;
};
auto tmp = new T [capacity_];
std::copy(arr_, arr_+size_, tmp+1);
delete [] arr_;
arr_ = tmp;
arr_[0] = o;
size_++;
return *this;
};
 
template <typename T>
MojVektor<T>& MojVektor<T>::push_back(T&& o){
if(size_ == capacity_){
realoc();
};
arr_ [size_++] = std::move(o);
return *this;
}; 

template <typename T>
MojVektor<T>& MojVektor<T>::push_front(T&& o){
 if(size_ == capacity_){
capacity_*=2;
};
auto tmp = new T [capacity_];
std::copy(arr_, arr_+size_, tmp+1);
delete [] arr_;
arr_ = tmp;
arr_[0] = std::move(o);
size_++;
return *this;
};


template <typename T>
T* MojVektor<T>::data(){
return arr_;
}

template <typename T>
void MojVektor<T>::clear(){
MojVektor<T>::~MojVektor();
};

template <typename T>
void MojVektor<T>::resize(size_t newSize, const T& difference_value){
if (size_== newSize){
return ;
}else if (newSize < size_){
size_=newSize;
}else {
auto oldSize= size_;  
capacity_ = size_ = newSize;
auto tmp = new T [capacity_];
std::fill_n(tmp, capacity_, difference_value);
std::copy(arr_, arr_+oldSize, tmp);
delete [] arr_;
arr_ = tmp;
};
}

template <typename T>
MojVektor<T>& MojVektor<T>::pop_back(){
if (size_ == 0) throw std::out_of_range{"Van granica!"};
size_--;
};

template <typename T>
MojVektor<T>& MojVektor<T>::pop_front(){
if (size_ == 0) throw std::out_of_range{"Van granica!"};
for(int i = 0; i < size_ ; i++){
arr_[i] = arr_[i+1];
};
size_--;
return *this;
};

template <typename T>
T& MojVektor<T>::back() const{
if(size_ == 0) throw std::out_of_range{"Van granica"};
return arr_[size_-1];
};

template <typename T>
T& MojVektor<T>::front() const{
if(size_ == 0) throw std::out_of_range{"Van granica"};
return arr_[0];
 };

template <typename T>
  bool MojVektor<T>::operator==(const MojVektor& o) const{
  if ( size_ == o.size_){
  for(int i=0;i<size_;i++){
  if (arr_[i] != o.arr_[i]){
    return false;
  };
  };
  return true;
  }else{
    return false;
  };
  };

template <typename T>
 bool MojVektor<T>::operator!=(const MojVektor& o) const{
 return !(*this == o);
 };

template <typename T>
bool MojVektor<T>::full() const{
return size_==capacity_;
};

template <typename T>
class MojVektor<T>::Iterator 
: public std::iterator<std::random_access_iterator_tag,T>{
  public:

  Iterator(): pt_{nullptr}{}; 
  Iterator(T* o) : pt_{o}{};
  Iterator(const Iterator& other){
  pt_ = other.pt_;
  };
  Iterator(Iterator&& other){
  pt_= other.pt_;
  other.pt_ = nullptr;
  }
  
  Iterator& operator=(const Iterator& other){
  pt_ = other.pt_;
  return *this;
  };
  Iterator& operator=(Iterator&& other){
  pt_ = other.pt_;
  other.pt_= nullptr;
  return *this;
  }; 

   T* operator[](size_t el){
   return pt_+el;
   };
 

  T* operator->(){
  return pt_;
  }

  Iterator operator+(int n){
  return Iterator{pt_+n};
  };

 Iterator operator-(int n){
  return Iterator{pt_-n};
  };

  size_t operator-(const Iterator& o){
  return pt_ - o.pt_;
  };

  size_t operator+(const Iterator& o){
  return pt_ + o.pt_;
  }

  bool operator!=(const Iterator& o){
  return pt_ != o.pt_;
  };

  bool operator==(const Iterator& o){
  return pt_==o.pt_;
  }

  bool operator<(const Iterator& o){
  return pt_<o.pt_;
  }

 bool operator<=(const Iterator& o){
  return pt_<=o.pt_;
  }

 bool operator>(const Iterator& o){
  return pt_>o.pt_;
  }

 bool operator>=(const Iterator& o){
  return pt_>=o.pt_;
  }

  Iterator operator++(int){
  return Iterator{pt_++};
  }

  Iterator& operator++(){
  ++pt_;
  return *this;
  }
 
Iterator operator--(int){
  return Iterator{pt_--};
  }

  Iterator& operator--(){
  --pt_;
  return *this;
  }

  T& operator*(){
  return *pt_;
  }
 
 //if (element > end()) throw std::out_of_range{"Indeks van granica

  private:
  T* pt_;
};
//samo operatore u iterator klasi, ostatak kao Vector metode
template <typename T>
MojVektor<T> MojVektor<T>::subvector(Iterator begin, Iterator end){
  MojVektor<T> sub;
  while (begin != end){
  sub.push_back(*begin);
  begin++;
  };
  return sub;
  }
template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::begin() const{
 return Iterator{arr_};
 };

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::end() const{
  return Iterator{arr_+size_};
};

template <typename T>
 typename MojVektor<T>::Iterator MojVektor<T>::find(const T& el) const{
 if(size_ == 0) return end();
 Iterator finder = begin();
 while(finder != end()){
   if (*finder == el) return finder;
   finder++;
 }
   return end();
 };
  template <typename T>
 typename MojVektor<T>::Iterator MojVektor<T>::erase(Iterator pos){
if(size_ == 0) return end();
if(pos == end()) return end();

Iterator tmp = pos;
while(pos != end()){
*pos = *(pos+1);
pos++;
};
size_--;
return tmp;
 };

  template <typename T>
 typename MojVektor<T>::Iterator MojVektor<T>::insert(Iterator pos, const T& o){
 if(pos >= end()) throw std::out_of_range{"Invalid position!"};  
 if(pos == begin()) {
   push_front(o);
   return begin();
 };
size_t ind = pos-begin();
 if(size_ == capacity_){
   realoc();
 };
for(size_t i=size_; i > ind; --i){
arr_[i] = arr_[i-1];
};
arr_[ind] = o;
size_++;
return begin()+ind; 
};

  template <typename T>
 typename MojVektor<T>::Iterator MojVektor<T>::insert(Iterator pos, T&& o){
 if(pos >= end()) throw std::out_of_range{"Invalid position!"};  
 if(pos == begin()){
   push_front(std::move(o));
 return begin();
 };
size_t ind = pos-begin();
 if(size_ == capacity_){
   realoc();
 };
for(size_t i=size_; i>ind;--i){
arr_[i] = arr_[i-1];
};
arr_[ind] = std::move(o);
size_++;
return begin()+ind;
};

  template <typename T>
 typename MojVektor<T>::Iterator MojVektor<T>::rbegin() const{
 return end()-1;
 };
  template <typename T>
 typename MojVektor<T>::Iterator MojVektor<T>::rend() const{
 return begin()-1;
 };

template <typename T>
 typename MojVektor<T>::Iterator MojVektor<T>::erase(Iterator beginIt, Iterator endIt){
 size_t differential = endIt-beginIt;
 size_t to_begin = beginIt - begin();
for(size_t i = to_begin; i<size_; i++){
arr_[i] = arr_[i + differential];
};
size_ -= differential;
return begin() + to_begin;
 };


template <typename T>
void MojVektor<T>::rotate(){
int counter = size()/2;
auto it1= begin();
auto it2= end() - 1;
for(int i=0; i< counter; i++){
  std::swap(*it1, *it2);
  it1++;
  it2--;
};
};

  template <typename T>
void MojVektor<T>::rotate(Iterator beginIt, Iterator endIt){
size_t  interval = endIt - beginIt;
int counter = interval/2;
endIt--;
for(int i= 0; i<counter; i++){
  std::swap(*beginIt, *endIt);
  beginIt++;
  endIt--;
};

};


