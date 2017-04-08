        #ifndef _QUADRATIC_PROBING_H_
        #define _QUADRATIC_PROBING_H_

        #include "Node.h"
        #include "vector.h"
        //#include "mystring.h"

        // QuadraticProbing Hash table class
        //
        // CONSTRUCTION: an initialization for ITEM_NOT_FOUND
        //               and an approximate initial size or default of 101
        //
        // ******************PUBLIC OPERATIONS*********************
        // void insert( x )       --> Insert x
        // void remove( x )       --> Remove x
        // Hashable find( x )     --> Return item that matches x
        // void makeEmpty( )      --> Remove all items
        // int hash( String str, int tableSize )
        //                        --> Static method to hash strings

        class QuadraticHashTable
        {
          public:
            QuadraticHashTable(int size = 101 );
            QuadraticHashTable( const QuadraticHashTable & rhs )
              : array( rhs.array),
                currentSize( rhs.currentSize ) {ITEM_NOT_FOUND = new Node();}

            Node* find( char x[] );

            void makeEmpty( );
            void insert(Node* x );
            void remove(Node* x );

            enum EntryType { ACTIVE, EMPTY, DELETED };
          private:
            struct HashEntry
            {
                Node* element;
                EntryType info;

                HashEntry( Node* e = new Node(), EntryType i = EMPTY )
                  : element( e ), info( i ) { }
            };

            vector<HashEntry> array;
            int currentSize;
            Node* ITEM_NOT_FOUND;
            bool isPrime( int n ) const;
            int nextPrime( int n ) const;
            bool isActive( int currentPos ) const;
            int findPos( Node * x ) const;
            int findPos(char x[]);
            int hash( const char key[], int tableSize ) const;
            int hash( int key, int tableSize ) const;
            void rehash( );
        };
        #endif