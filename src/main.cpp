#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <unistd.h>

std::vector<uint_fast32_t> stack;
uint_fast32_t stack_pos = 0;

std::vector<uint_fast16_t> program;
uint_fast32_t prog_pos = 0;

std::vector<uint_fast16_t> jumplist;

void init(std::vector<std::string> args)
{
  // Init the stack
  stack.push_back(0);
  // Turn argv into the program
  for(auto w : args)
  {
    for(auto c : w)
    {
      program.push_back((int)c);
    }    
  }
  // Add piped input to the end of the program
  if(!(isatty(fileno(stdin))))
  {
    std::string piped;
    while(std::cin >> piped)
    {
      for(auto c : piped)
      {
        program.push_back((int)c);
      }
    }
  }
}

void selectn()
{
  if(stack_pos + 1 > stack.size())
  {
    stack.push_back(0);
    stack_pos++;
  }
}

void selectp()
{
  if(stack_pos > 0)
  {
    stack_pos--;
  }
}

uint_fast32_t get()
{
  return stack[stack_pos];
}

void inc()
{
  if(get() < UINT_FAST32_MAX)
  {
    stack[stack_pos] = get() + 1;
  }
}

void dec()
{
  if(get() > 0)
  {
    stack[stack_pos] = get() - 1;
  }
}

void store()
{
  jumplist.push_back(get());
  stack[stack_pos] = 0;
  program[prog_pos] = 0;
}

void jmp()
{
  if(jumplist.size() > 0)
  {
    prog_pos = jumplist.back() - 1;
    jumplist.pop_back();
  }
}

void ifskip()
{
  if(get() == 0)
  {
    prog_pos += 1;
  }
}

void display()
{
  std::cout << (char)stack[stack_pos];
}

void literal()
{
  std::cout << stack[stack_pos];
}

void invert()
{
  std::reverse(stack.begin(), stack.end());
}

void reverse()
{
  std::reverse(program.begin(), program.end());
}

void clear()
{
  stack[stack_pos] = 0;
}

void eval()
{
  while(prog_pos < program.size())
  {
    switch((char)program[prog_pos])
    {
      case('+'):
        inc();
        prog_pos++;
        break;
      case('-'):
        dec();
        prog_pos++;
        break;
      case('?'):
        clear();
        prog_pos++;
        break;
      case('>'):
        selectn();
        prog_pos++;
        break;
      case('<'):
        selectp();
        prog_pos++;
        break;
      case('.'):
        store();
        prog_pos++;
        break;
      case(':'):
        jmp();
        prog_pos++;
        break;
      case('!'):
        ifskip();
        prog_pos++;
        break;
      case('%'):
        literal();
        prog_pos++;
        break;
      case('#'):
        display();
        prog_pos++;
        break;
      case('('):
        invert();
        prog_pos++;
        break;
      case(')'):
        reverse();
        prog_pos++;
        break;
      default:
        prog_pos++;
    }
  }
}

int main(int argc, char** argv)
{
  std::vector<std::string> args(argv + 1, argv + argc);
  init(args);
  eval();
  std::cout << std::endl;
}
