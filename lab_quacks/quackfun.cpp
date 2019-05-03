/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
	T sum(stack<T>& s)
	{
    // Your code here
		T total = T();
		T ele_top;
		if(!s.empty()){
			ele_top = s.top();
      s.pop(); // pop the top element
      total += sum(s) + ele_top;
  }

    else{ // if the stack is empty
    	return T();
    }

    // push the element back
    s.push(ele_top);

    return total; // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
	stack<T> s;
	int block_size = 1;
	int queue_size = (int)q.size();

    // Your code here

	while(queue_size > 0){
		int real_size = block_size;

      if(queue_size < block_size){//check whether there are enough elements
      	real_size = queue_size;
      }

      queue_size -= real_size; // substract real number of elements that will be modified


			//handle leftovers as if they were complete
      if(block_size % 2 == 0){
          //even block size case
      	while(real_size != 0){
      		s.push(q.front());
      		q.pop();
      		real_size--;
      	}

      	while(!s.empty()){
      		q.push(s.top());
      		s.pop();
      	}



      }

      else{
        // odd block size case
      	while(real_size != 0){
      		q.push(q.front());
      		q.pop();
      		real_size--;
      	}

      }

      block_size++;

  }


}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    bool retval = true; // optional
    T temp1; // rename me
    //T temp2; // rename :)

    if(s.size() != 1){
    	temp1 = s.top();
    	s.pop();
    }

    else{ // when stack has only one element
      if(s.top() != q.front()){ // if element is not the same in base case
      	retval = false;
      }

      else{
      	// if element is the same in base case
      	//s.pop(); // pop out the last element(empty queue)
      	//q.pop(); // pop out the front element of current q(the modification will be stored)
      	retval = true;
      }
			q.push(q.front());
			q.pop();
			return retval;
  }

    //temp1 = q.front(); // store front element of queue before recursion
    retval = verifySame(s, q);
    s.push(temp1);
    if(retval){
    	if(s.top() == q.front()){
    		retval = true;


    	}

    	else{
    		retval = false;

    	}
    }

    else{
    	retval = false;
    }

    q.push(q.front());
    q.pop();


    return retval;
}

}
