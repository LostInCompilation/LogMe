/*
    The zlib License

    Copyright (C) 2024 Marc Schöndorf
 
This software is provided 'as-is', without any express or implied warranty. In
no event will the authors be held liable for any damages arising from the use of
this software.

Permission is granted to anyone to use this software for any purpose, including
commercial applications, and to alter it and redistribute it freely, subject to
the following restrictions:

1.  The origin of this software must not be misrepresented; you must not claim
    that you wrote the original software. If you use this software in a product,
    an acknowledgment in the product documentation would be appreciated but is
    not required.

2.  Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

3.  This notice may not be removed or altered from any source distribution.
*/

/*------------------------------------------------------------------*/
/*                                                                  */
/*                          LOG ME LIBRARY                          */
/*                                                                  */
/*                      (C) 2024 Marc Schöndorf                     */
/*                            See license                           */
/*                                                                  */
/*  SharedQueue.hpp                                                 */
/*  Created: 19.11.2024                                             */
/*------------------------------------------------------------------*/

namespace LogMe
{
template <typename T>
class SharedQueue
{
private:
    std::queue<T>   m_Queue;
    std::mutex      m_Mutex;
    
public:
    SharedQueue() {}
    //~SharedQueue();
    
    SharedQueue(const SharedQueue& other) = delete;
    SharedQueue& operator=(const SharedQueue& other) = delete;
    
    void Push(const T& element)
    {
        std::scoped_lock<std::mutex> lock(m_Mutex);
        m_Queue.push(element);
    }
    
    bool Front(T& element) const
    {
        std::scoped_lock<std::mutex> lock(m_Mutex);
        
        if(m_Queue.empty())
            return false;
        
        element = m_Queue.front();
        
        return true;
    }
    
    bool Pop(T& element)
    {
        std::scoped_lock<std::mutex> lock(m_Mutex);
        
        if(m_Queue.empty())
            return false;
        
        element = std::move(m_Queue.front());
        m_Queue.pop();
        
        return true;
    }
    
    bool IsEmpty() const
    {
        std::scoped_lock<std::mutex> lock(m_Mutex);
        return m_Queue.empty();
    }
    
    std::size_t GetSize() const
    {
        std::scoped_lock<std::mutex> lock(m_Mutex);
        return m_Queue.size();
    }
};
}
