#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <vector>
#include <iostream>
template <typename KeyType, typename ValueType>
class TreeMultimap
{
private:
  struct Node
  {
      Node() // node constructor, is this needed?
      {
          m_left = nullptr;
          m_right = nullptr;
      }
      KeyType m_key;
      Node* m_left;
      Node* m_right;
      std::vector<ValueType> m_objects;
  };
  Node* m_root;
  
  void insertHelper (Node* &currNode, KeyType key, ValueType value) // recursion to insert into trees
  {
      if (currNode == nullptr) // no tree created yet, create first node
      {
          
          currNode = new Node;
          currNode->m_key = key;
          currNode->m_objects.push_back(value);
          currNode->m_left = nullptr;
          currNode->m_right = nullptr;
      }
      else if (key == currNode->m_key)
      {
          currNode->m_objects.push_back(value); // same actor or director or genre must hold all the movies they correspond with
          return;
      }
      else if (key < currNode->m_key)
      {
          insertHelper(currNode->m_left, key, value); 
      }
      else
      {
          insertHelper(currNode->m_right, key, value);
      }
  }
  
  void deleteHelper(Node* currNode)
  {
      if (currNode != nullptr)
      {
          deleteHelper(currNode->m_left);
          deleteHelper(currNode->m_right);
          delete currNode;
      }
  }
    
    void desctructorHelper(Node* curr)
    {
        if (curr == nullptr)
            return;
    
        desctructorHelper(curr->m_left);
        desctructorHelper(curr->m_right);
        
        delete(curr);
    }

    
  public:
    class Iterator
    {
      public:
        Iterator()
        {
            m_ptr = nullptr;
            m_isvalid = false;
            m_vectorPtr = nullptr;
        }

        Iterator(Node* nodePtr)
        {
            m_ptr = nodePtr;
            m_vectorPtr = &(m_ptr->m_objects[0]); // pointing at first object in vector with given key
            m_isvalid = true;
            m_size = m_ptr->m_objects.size();
            m_index = 0;
        }
        ValueType& get_value() const
        {
            return *m_vectorPtr;
        }

        bool is_valid() const
        {
            if (m_index >= m_size)
            {
                return false;
            }
            return m_isvalid;  // Replace this line with correct code.
        }

        void advance()
        {
            m_vectorPtr++;
            m_index++;
            // Replace this line with correct code.
        }

      private:
        Node* m_ptr;
        bool m_isvalid;
        ValueType* m_vectorPtr; 
        int m_size;
        int m_index;
    };

    TreeMultimap()
    {
        m_root = nullptr;
        
        // Replace this line with correct code.
    }

    ~TreeMultimap()
    {
        desctructorHelper(m_root);
    }
    
    void insert(const KeyType& key, const ValueType& value)
    {
        KeyType copyKey = key;
        ValueType copyValue = value;
        insertHelper(m_root, copyKey, copyValue);
        // Replace this line with correct code.
    }

    Iterator find(const KeyType& key) const
    {
        Node* ptr = m_root;
        while (ptr != nullptr)
        {
            if (key == ptr->m_key)
                return Iterator(ptr);
            else if (key < ptr->m_key)
                ptr = ptr->m_left;
            else
                ptr = ptr->m_right;
        }
        return Iterator(); // returns a bad iterator pointing to null
    }
    
};

#endif // TREEMULTIMAP_INCLUDED
