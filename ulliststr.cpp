#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

  /**
   * Adds a new value to the back of the list
   *   - MUST RUN in O(1)
   */
void ULListStr::push_back(const std::string& val){
  if(head_ == NULL && tail_ == NULL){
    head_ = new Item();
    tail_ = head_;
    head_->val[0] = val;
    head_->first = 0;
    head_->last = 1;
    head_->prev = NULL;
    tail_->prev = NULL;
    size_++;
  }

  else if(tail_->last == ARRSIZE){
    Item* temp = tail_;
    tail_->next = new Item();
    tail_ = tail_->next;
    tail_->val[0] = val;
    tail_->first = 0;
    tail_->last = 1;    
    tail_->prev = temp;
    tail_->next = NULL;
    size_++;

  }
  else{
    tail_->val[tail_->last] = val;
    (tail_->last)++;
    size_++;

  }


}

  void ULListStr::push_front(const std::string& val){
  if(head_ == NULL && tail_ == NULL){
    head_ = new Item();
    head_->val[ARRSIZE - 1] = val;
    head_->first = ARRSIZE-1;
    head_->last = ARRSIZE;   
    head_->next = NULL;
    head_->prev = NULL;
    tail_ = head_;

    size_++;  
  }

  else if(head_->first == 0){
    Item* temp = head_;
    head_->prev = new Item();
    head_ = head_->prev;
    head_->prev = NULL;
    head_->val[ARRSIZE - 1] = val;
    head_->first = ARRSIZE-1;
    head_->last = ARRSIZE;    
    head_->next = temp;
    size_++;

  }
  else{
    Item* temp = head_;
    head_->val[head_->first - 1] = val;
    (head_->first)--;

    size_++;
  }


  }


  /**
   * Removes a value from the back of the list
   *   - MUST RUN in O(1)
   */
  void ULListStr::pop_back(){
    if(size_ == 1){
        delete tail_;
        tail_ = NULL;
        head_ = NULL;
        size_--;

    }
    else if(size_ <= ARRSIZE){

      
      tail_->last = (tail_->last)-1;
      size_--;
    }
    else if(tail_->last - tail_->first == 1){
      size_--;
      Item* temp = tail_->prev;
      temp->next = NULL;
      delete tail_;
      tail_ = temp;
      
      
    }
    else{
      tail_->last = (tail_->last)-1;
      size_--;
    }
  }

  void ULListStr::pop_front(){
    if(size_ == 1){
        delete head_;
        size_--;
        tail_ = NULL;
        head_ = NULL;

 
      }
    else if(size_ <= ARRSIZE){

      
      head_->first = (head_->first)+1;
      size_--;
      }
    

    else if(head_->last - head_->first == 1){
      size_--;
      Item* temp = head_->next;
      temp->prev = NULL;
      delete head_;
      head_ = temp;
    
    }
    else{
      head_->first = (head_->first)+1;
      size_--;
    }
  }

  /**
   * Returns a const reference to the back element
   *   - MUST RUN in O(1)
   */
  std::string const & ULListStr::back() const{
    return (tail_->val[(tail_->last)-1]);
  }

  std::string const & ULListStr::front() const{
    return (head_->val[(head_->first)]);
  }

    /* Returns a pointer to the item at index, loc,
   *  if loc is valid and NULL otherwise
   *   - MUST RUN in O(n) 
   */
  std::string* ULListStr::getValAtLoc(size_t loc) const{
    if(loc >= size_){
      return NULL;  
    }
    Item* temp = head_;
    int count = 0;
    while(count + temp->last - temp->first <= loc){
      count += temp->last - temp->first;
      temp = temp->next;
    }
    return &(temp->val[loc - count + temp->first]);
  }




