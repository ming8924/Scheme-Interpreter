/**
 * \file Cell.cpp
 *
 * An implementation of the Cell.hpp interface, to support the cons list ADT interface specified
 * in cons.hpp. The functions here will be called in Cons.hpp in order to 
 * build the tree structure.
 */


#include "eval.hpp"

map<string,Cell*> symbol_table;
list< map<string,Cell*> > map_list;

int operand_num(Cell* c)
{
   Cell*cur=c;
   int ctr=0;
   while(cur!=nil)
   {
      cur=cur->get_cdr();
      ++ctr;
   }
   return ctr;
}


// Reminder: cons.hpp expects nil to be defined somewhere.  For this
// implementation, this is the logical place to define it.
Cell* const nil = 0;


IntCell::IntCell(const int i) 
{
  int_m=i;
}
bool IntCell::is_int() const{return true;}

int IntCell::get_int() const{return int_m;}

void IntCell::print(ostream& os) const
{os <<showpoint<<int_m;}

bool IntCell::if_operation()
{
   if (this->get_int()==0) return false;
   else return true;
}

bool IntCell::valid_type_four()
{
   return true;
}

Cell*  IntCell::addition(Cell* addened)
{
   if (addened->is_int())
   {
      return new IntCell(this->get_int()+addened->get_int());
   }
   else if(addened->is_double())
   return new DoubleCell(this->get_int()+addened->get_double());
}

Cell*  IntCell::multiplication(Cell* multed)
{
   if (multed->is_int())
   {
      return new IntCell(this->get_int() * multed->get_int());
   }
   else if(multed->is_double())
   return new DoubleCell(this->get_int() * multed->get_double());
}

Cell* IntCell::subtraction(Cell* sub)
{
   if (sub->is_int())
   {
      return new IntCell(this->get_int()- sub->get_int());
   }
   else if(sub->is_double())
   return new DoubleCell(this->get_int()- sub->get_double());
}

Cell* IntCell::division(Cell* div)
{
   if(!div->if_operation()){
      throw runtime_error("Zero can't be a divider");
   }
   if (div->is_int())
   {
      return new IntCell(this->get_int()/div->get_int());
   }
   else if(div->is_double())
   return new DoubleCell(this->get_int()/div->get_double());
}

bool IntCell::smaller(Cell* operand)
{
   if (operand->is_int())
   {
      if(this->get_int()<operand->get_int())
      return true;
      else return false;
   }
   else if (operand->is_double())
   {
      if(this->get_int()<operand->get_double())
      return true;
      else return false;
   }
   else throw runtime_error("Invalid comparison");
}







DoubleCell::DoubleCell(const double d)
{
  double_m=d;
}

bool DoubleCell::is_double() const{return true;}

double DoubleCell::get_double() const{return double_m;}

void DoubleCell::print(ostream& os) const
{os <<showpoint<<double_m;}

int DoubleCell::ceiling_operation()
{
   return ceil(get_double());
}

int DoubleCell::floor_operation()
{
   return floor(get_double());
}

bool DoubleCell::if_operation()
{
   if (this->get_double()==0) return false;
   else return true;
}

bool DoubleCell::valid_type_four()
{
   return true;
}

Cell*  DoubleCell::addition(Cell* addened)
{
   if (addened->is_int())
   {
      return new DoubleCell(this->get_double()+addened->get_int());
   }
   else if(addened->is_double())
   return new DoubleCell(this->get_double()+addened->get_double());
}

Cell*  DoubleCell::multiplication(Cell* multed)
{
   if (multed->is_int())
   {
      return new DoubleCell(this->get_double() * multed->get_int());
   }
   else if(multed->is_double())
   return new DoubleCell(this->get_double() * multed->get_double());
}

Cell*  DoubleCell::subtraction(Cell* sub)
{
   if (sub->is_int())
   {
      return new DoubleCell(this->get_double()- sub->get_int());
   }
   else if(sub->is_double())
   return new DoubleCell(this->get_double() - sub->get_double());
}

Cell*  DoubleCell::division(Cell* div)
{
   if(!div->if_operation()){
      throw runtime_error("Zero can't be a divider");
   }
   if (div->is_int())
   {
      return new DoubleCell(this->get_double()/div->get_int());
   }
   else if(div->is_double())
   return new DoubleCell(this->get_double()/div->get_double());
}

bool DoubleCell::smaller(Cell* operand)
{
   if (operand->is_int())
   {
      if(this->get_double()<operand->get_int())
      return true;
      else return false;
   }
   if (operand->is_double())
   {
      if(this->get_double()<operand->get_double())
      return true;
      else return false;
   }
   else throw runtime_error("Invalid comparison");
}






SymbolCell::SymbolCell(const char* const s)
{
  symbol_m=new char[strlen(s)];  /////  don't forget to destruct it
  strcpy(symbol_m,s);
}

bool SymbolCell::is_symbol() const{return true;}

string SymbolCell::get_symbol() const{return symbol_m;}

void SymbolCell::print(ostream& os) const
{os <<showpoint<<symbol_m;}

bool SymbolCell::if_operation()
{
   return true;
}

bool SymbolCell::is_operator()
{
    if(this->get_symbol()=="+"||
       this->get_symbol()=="-"||
       this->get_symbol()=="*"||
       this->get_symbol()=="/"||
       this->get_symbol()=="ceiling"||
       this->get_symbol()=="floor"||
       this->get_symbol()=="if"||
       this->get_symbol()=="quote"||
       this->get_symbol()=="cons"||
       this->get_symbol()=="car"||
       this->get_symbol()=="cdr"||
       this->get_symbol()=="nullp"||
       this->get_symbol()=="not"||
       this->get_symbol()=="define"||
       this->get_symbol()=="print"||
       this->get_symbol()=="eval"||
       this->get_symbol()=="<" ||
       this->get_symbol()=="intp"||
       this->get_symbol()=="doublep"||
       this->get_symbol()=="listp"||
       this->get_symbol()=="symbolp"||
       //this->get_symbol()=="procedurep"||
       this->get_symbol()=="apply"||
       this->get_symbol()=="let"||
       this->get_symbol()=="lambda") return true;
    else return false;
}

bool SymbolCell::procedure_built_in()
{
    if(this->get_symbol()=="+"||
       this->get_symbol()=="-"||
       this->get_symbol()=="*"||
       this->get_symbol()=="/"||
       this->get_symbol()=="ceiling"||
       this->get_symbol()=="floor"||
       this->get_symbol()=="cons"||
       this->get_symbol()=="car"||
       this->get_symbol()=="cdr"||
       this->get_symbol()=="not"||
       this->get_symbol()=="print"||
       this->get_symbol()=="eval"||
       this->get_symbol()=="<" ) return true;
    else return false;
}


bool SymbolCell::smaller(Cell* operand)
{
   if(operand->is_symbol())
   {
      if(this->get_symbol()<operand->get_symbol())
      return true;
      else return false;
   }
   else throw runtime_error("Invalid comparison");
}







ConsCell::ConsCell(Cell* const my_car, Cell* const my_cdr)
{
  car=my_car;
  cdr=my_cdr;
}

bool ConsCell::is_cons() const{return true;}

Cell* ConsCell::get_car() const{return car;}

Cell* ConsCell::get_cdr() const{return cdr;}

void ConsCell::print(ostream& os) const
{//cout<<"print cons"<<endl;
   const Cell* cur=this;
   if(this->is_cons())
   os <<"(";
   else this->print(os);
   while (cur!=nil)
   {
      if (cur->get_car()==nil) {cout<<"()";cur=cur->get_cdr();cout<<" ";}
      else{
         cur->get_car()->print(os);//cout<<"print car"<<endl;
         cur=cur->get_cdr();cout<<" ";
      }
   }
   os<<"\b)";
}

bool ConsCell::if_operation()
{
   return true;
}








ProcedureCell:: ProcedureCell(Cell* const my_formals,Cell* const my_body)
{
   formals=my_formals;
   body=my_body;
}

Cell*  ProcedureCell:: get_formals() const {return formals;}
Cell*  ProcedureCell:: get_body() const {return body;}
bool ProcedureCell:: is_procedure() const{return true;}
bool ProcedureCell:: if_operation() {return true;}
void ProcedureCell:: print(ostream& os) const{os<<"#<function>";}

Cell* ProcedureCell::  apply(Cell*args)
{     
      map<string,Cell*> local_table;
      if(this->get_formals()!=nil)
      {
         Cell* formal_count=this->get_formals();
         Cell* argument_count=args;
         if(!listp(args)) 
         {throw runtime_error("Must receice a list of arguments");}
         if(operand_num(this->get_formals())!=operand_num(args))
         {throw runtime_error("Wrong number of arguments");}
         else{
            //cout<<"1"<<endl;
            while (formal_count!=nil)
            {
               local_table[formal_count->get_car()->get_symbol()]=eval(argument_count->get_car());
               formal_count=formal_count->get_cdr();
               argument_count=argument_count->get_cdr();
            }
            map_list.push_front(local_table);//the new table is push in the front
         }
      }
      Cell* eval_count=this->get_body();//cout<<"2 "<<*eval_count<<endl;
      Cell* result;
      try{
      while (eval_count->get_cdr()!=nil)
      {  //cout<<"3"<<endl;
         eval(eval_count->get_car());//cout<<"4"<<endl;
         eval_count=eval_count->get_cdr();
         
      }
      result=eval(eval_count->get_car());
      }
      catch(runtime_error & e)
      {map_list.pop_front();throw e;}
      if(this->get_formals()!=nil) map_list.pop_front();
      return result;
} 


