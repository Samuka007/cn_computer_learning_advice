---
title: "Tower of Hanoi I"
date: 2023-09-03T13:41:52+08:00
authors: 
    - "Samuka007"
categories: "guide"
tags:
    - "C++"
    - "Program"
summary: Classic tower of Hanoi recursion solution, with graphic display.
draft: false
---
## Introduct

A classic 'tower of Hanoi' recursion solution, with graphic display.

## Code

Godbolt: <https://godbolt.org/z/5z33oTPK4>

```c++
#include    <thread>
#include    <stack>
#include    <string>
#include    <iomanip>
#include    <iostream>
#include    <vector>

// helper for printing same chars
namespace help {
    inline void putchars( size_t n, char c ) {
        std::cout << std::setfill(c) << std::setw(n) << "";
    }
}

class Disk
{
public:
    Disk( size_t size ) : _size { size } {}
    inline size_t size() const { return _size; }
private:
    size_t _size; // radius
};

class Tower : public std::stack<Disk>
// It's obvious that a Tower is a stack of disk
{
public:
    Tower( size_t height ) : height ( height ) {}
    // height == max radius
    void print()
    {
        for ( size_t i = 0; i < height - this->size() + 1; ++i ) {
            help::putchars(this->size() + 2, ' ');
            std::cout << '|';
            help::putchars(this->size() + 2, ' ');
            std::cout << '\n';
        }
        for ( const auto& disk : this->c ) {
            help::putchars( height - disk.size() + 1, ' ' );
            std::cout << '<';
            help::putchars( disk.size() * 2 + 1, '=' );
            std::cout << '>';
            help::putchars( height - disk.size() + 1, ' ' );
            std::cout << '\n';
        }
    }

    void print_by_line ( size_t line ) 
    // line start by 0
    {
        size_t head = height - this->size() + 1;
        if ( line < head ) {
            help::putchars( height + 2, ' ');
            std::cout << '|';
            help::putchars( height + 2, ' ');
        } else {
            auto& disk = this->c.at( this->size() - line + head - 1 );
            // Should have a better way to locate, but what ever
            help::putchars( height - disk.size() + 1, ' ' );
            std::cout << '<';
            help::putchars( disk.size() * 2 + 1, '=' );
            std::cout << '>';
            help::putchars( height - disk.size() + 1, ' ' );
        }
    }

    void operator>> ( Tower& rhs )
    // reload for moving the top disk to rhs
    {
        rhs.push( this->top() );
        this->pop();
    }

private:
    size_t height;
};

class Hanoi3 : protected std::vector<Tower>
{
public:
    static constexpr size_t col_num = 3;

    Hanoi3 ( size_t disk_num = 3 )
    :   std::vector<Tower> ( col_num, Tower(disk_num) ), height ( disk_num ) {
        for ( size_t i=disk_num; i>0; --i ) {
            this->at(0).push(Disk(i));
        }
    }

    // recursion entry
    void recursion()
    {
        print(0); // print step 0
        _recursion( this->at(0), this->at(1), this->at(2), height );
    }

    // Main recursion function
    void _recursion( Tower& src, Tower& des, Tower& mid, size_t mv_size )
    {
        static size_t step {1}; // log step

        if ( mv_size == 1 ) {
            src >> des ;
            print( step++ );
            return ;
        }
        _recursion( src, mid, des, mv_size-1 );
        src >> des;
        print( step++ );
        _recursion( mid, des, src, mv_size-1);
    }

    void print()
    {
        help::putchars(this->size() * ( 2 * ( height + 2 ) + 1), '+');
        std::cout << '\n';
        _print();
    }

private:
    size_t height;

    void print( size_t step )
    {
        std::cout << std::setfill('+') 
                  << std::setw(this->size() * ( 2 * ( height + 2 ) + 1)) 
                  << std::left
                  << ("step " + std::to_string(step))
                  << '\n';
        _print();
    }

    void _print()
    {
        for ( size_t i=0 ; i<height+1 ; ++i ) {
            for ( auto& tow : *this ) {
                tow.print_by_line ( i );
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
};


int main()
{
    // call hanoi recurison solusion and print the animation.
    Hanoi3(3).recursion();
}
```

## Result

```shell
Program returned: 0
Program stdout
step 0+++++++++++++++++++++++++++
     |          |          |     
   <===>        |          |     
  <=====>       |          |     
 <=======>      |          |     

step 1+++++++++++++++++++++++++++
     |          |          |     
     |          |          |     
  <=====>       |          |     
 <=======>    <===>        |     

step 2+++++++++++++++++++++++++++
     |          |          |     
     |          |          |     
     |          |          |     
 <=======>    <===>     <=====>  

step 3+++++++++++++++++++++++++++
     |          |          |     
     |          |          |     
     |          |        <===>   
 <=======>      |       <=====>  

step 4+++++++++++++++++++++++++++
     |          |          |     
     |          |          |     
     |          |        <===>   
     |      <=======>   <=====>  

step 5+++++++++++++++++++++++++++
     |          |          |     
     |          |          |     
     |          |          |     
   <===>    <=======>   <=====>  

step 6+++++++++++++++++++++++++++
     |          |          |     
     |          |          |     
     |       <=====>       |     
   <===>    <=======>      |     

step 7+++++++++++++++++++++++++++
     |          |          |     
     |        <===>        |     
     |       <=====>       |     
     |      <=======>      |     
```
