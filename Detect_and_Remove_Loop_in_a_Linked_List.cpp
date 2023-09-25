Detect and Remove Loop in a Linked List

1st Method :- Brute Force Method:

The idea is to iterate through each node and check if any of the subsequent nodes 
  have been visited before.
If a loop is detected, you can use another loop to find the last node of the loop 
  (the node whose next pointer points to the loop's starting node) and set its next pointer 
  to nullptr to break the loop.

 /////////////////////////////code///////////////////////////////////
void removeLoop(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        Node* runner = current->next;
        while (runner != nullptr) {
            if (current == runner) {
                // Loop detected, find the last node of the loop
                Node* lastOfLoop = current;
                while (lastOfLoop->next != current) {
                    lastOfLoop = lastOfLoop->next;
                }

                // Break the loop by setting the next pointer of the last node to nullptr
                lastOfLoop->next = nullptr;
                return;
            }
            runner = runner->next;
        }
        current = current->next;
    }
}
//TC : O(n^2) where n is the number of nodes in the linked list
//SC : O(1)

/*-----------------------------------------------------------------------------*/

2nd Method :- Efficient Method (Floyd's Cycle Detection Algorithm):

Floyd's Cycle Detection Algorithm, also known as the "tortoise and hare" algorithm, provides an efficient 
way to detect a loop in a linked list with a time complexity of O(n).
  
Steps:-
  1. Initialize two pointers, slow and fast, both initially pointing to the head of the linked list.
  2. Traverse the list using two pointers:
   - Move the slow pointer one step at a time.
   - Move the fast pointer two steps at a time.
  3. If there is a loop, the fast pointer will eventually catch up to the slow pointer, resulting in them 
     meeting at some point within the loop. If there is no loop, the fast pointer will reach the end of the list.
  4. Once they meet, reset one of the pointers (either fast or slow) to the head of the list and keep the other pointer at the meeting point.
  5. Move both pointers one step at a time. The point where they meet again is the start of the loop.

  /////////////////////////Code/////////////////////////////////
void removeLoop(Node* head) {
    Node* slow = head;
    Node* fast = head;
    bool loopDetected = false;

    // Detect loop
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            loopDetected = true;
            break;
        }
    }

    if (loopDetected) {
        slow = head;
        while (slow->next != fast->next) {
            slow = slow->next;
            fast = fast->next;
        }
        fast->next = nullptr; // Remove the loop
    }
}

//O(n) , O(1)

/*-----------------------------------------------------------------*/

3rd Method :- Hashing: Hash the address of the linked list nodes*

We can hash the addresses of the linked list nodes in an unordered map and just check 
if the element already exists in the map. If it exists, we have reached a node 
that already exists by a cycle, hence we need to make the last node’s next pointer NULL.

void removeCycle(Node* head) {
    Node* prev = nullptr; // previous pointer
    Node* curr = head;    // current pointer

    // Maintain an unordered_set to store visited nodes
    std::unordered_set<Node*> nodeSet;

    // Traverse the list
    while (curr != nullptr) {
        if (nodeSet.find(curr) != nodeSet.end()) { // If set contains the current node
            prev->next = nullptr;
            return;
        }

        // Insert the current node into the set
        nodeSet.insert(curr);

        // Update the prev pointer to the current node and move the curr pointer to the next node
        prev = curr;
        curr = curr->next;
    }
}
//O(n) , O(n)
