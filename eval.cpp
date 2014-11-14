/**
 * \file eval.cpp
 *
 * The function in this file evaluates the result of the expression tree 
 * whose root is pointed by c
 *
 */

#include "eval.hpp"


Cell* ceiling(Cell* o)
{
   	 if(operand_num(o)==0||operand_num(o)>=2)//Check whether the operand number is valid 
	 {throw runtime_error("There must be exactly one operand for CEILING");}
	 else {
	    Cell* result=eval(o->get_car()); result->print();
	    if(result==nil)//Error if nil is loaded as an operand
	    {
	       throw runtime_error("Can't accept nil as an operand");
	    }
            Cell* ceiling_input=result;
            int ceil_result=ceiling_input->ceiling_operation();//call the ceil function in Cell.cpp
            return make_int(ceil_result);//return the ceil result
	 }
}

Cell* floor (Cell* o)
{
   	 if(operand_num(o)==0||operand_num(o)>=2)
	 {throw runtime_error("There must be exactly one operand for FLOOR");}//Check whether the operand number is valid 
	 else {
	    Cell* result=eval(o->get_car());//cout<<"floor"<<endl;
	    if(result==nil)
	    {
	       throw runtime_error("Can't accept nil as an operand");
	    }
            Cell* floor_input=result;
            int floor_result=floor_input->floor_operation();//call the floor function in Cell.cpp
            return make_int(floor_result);//return the ceil result
	 }
}

Cell* addition (Cell* o)
{
            if(operand_num(o)==0) return make_int(0);//If there is no operand return the identity number for addition 
            else{
            Cell* cur=o;
            Cell* result=make_int(0);
            while(cur!=nil)
            {  Cell* cell=eval(cur->get_car());
               if(cell==nil)//If nil is taken as an operand, exit the program
               {
                  throw runtime_error("Can't accept nil as an operand");}
               else if(cell->valid_type_four())//add up the value to the variable result if the oprand is valid
               {
                  result=result->addition(cell);
                  cur=cur->get_cdr();}
            }
            return result;//return the addition result
         }
}


Cell* multiplication(Cell* o)
{
            if(operand_num(o)==0) return make_int(1);//If there is no operand return the identity number fir multiplication 
            else{
            Cell* cur=o;
            Cell* result=make_int(1);
            while(cur!=nil)
            {  Cell* cell=eval(cur->get_car());
               if(cell==nil)//If nil is taken as an operand, exit the program
               {
                  throw runtime_error("Can't accept nil as an operand");}
               else if(cell->valid_type_four())//multiply the value to the variable result  if the oprand is valid
               {
                  result=result->multiplication(cell);
                  cur=cur->get_cdr();}
            }
            return result;//return the multiplication result
         }
}

Cell* subtraction(Cell* o)
{
         if(operand_num(o)==0) {
         throw runtime_error("There must be at least one operand for SUBTRACTION");//Check whether the operand number is valid 
         }
         Cell* cell=eval(o->get_car());
         if(cell==nil)
         {throw runtime_error("Can't accept nil as an operand");}
         if(operand_num(o)==1)//if there is only one oprand and if the oprand is valid, return the negated value of the operand
         {
            if(cell->valid_type_four())
            return make_int(0)->subtraction(cell);
         }
         else{
            Cell* tmp=make_int(0);
            Cell* result=cell->addition(tmp);//construct the subtracted number
            Cell* cur=o->get_cdr();
            while(cur!=nil)
            {Cell* operand=eval(cur->get_car());
               if(operand==nil)
               {
                  throw runtime_error("Can't accept nil as an operand");}
               
               if(operand->valid_type_four())// if the oprand is valid subtract it from the passed object
               {result=result->subtraction(operand);
               cur=cur->get_cdr();}
            }
            return result;
         }
}

Cell* division(Cell* o)
{
         if(operand_num(o)==0) {
         throw runtime_error("There must be at least one operand for DIVISION");//Check whether the operand number is valid 
         }
         Cell* cell=eval(o->get_car());
         if(cell==nil)
         {throw runtime_error("Can't accept nil as an operand");}
         if(operand_num(o)==1)//if there is only one oprand and if the oprand is valid, return the inverse value of the operand
         {
            if(cell->valid_type_four())
            return make_int(1)->division(cell);
         }
         else{
            Cell* tmp=make_int(1);
            Cell* result=cell->multiplication(tmp);//construct the divided number
            Cell* cur=o->get_cdr();
            while(cur!=nil)
            {Cell* operand=eval(cur->get_car());
               if(operand==nil)
               {
                  throw runtime_error("Can't accept nil as an operand");}
               if(operand->valid_type_four())// if the oprand is valid divide it from the passed object
               {result=result->division(operand);
               cur=cur->get_cdr();}
            }
            return result;
         }
}


Cell* smaller (Cell* o)
{
   	 Cell* start=o;
	 bool makezero=false;
	 if(start==nil) return make_int(1);//no operand
	 else if (eval(start->get_car())==nil) throw runtime_error("Can't accept nil as an operand");
	 else if (!(eval(start->get_car())->is_cons()) && start->get_cdr()==nil) return make_int(1);
	 if(start!=nil) 
	 {
	    while (start->get_cdr()!=nil)
	    {  Cell* cell1=eval(start->get_car());
	       Cell* cell2=eval(start->get_cdr()->get_car());
	       if(cell1==nil || cell2==nil)
               {
                  throw runtime_error("Can't accept nil as an operand");}
	       else if(cell1->smaller(cell2))
	       {//if two consecutive operands not increasing
	          start=start->get_cdr();
	       }
	       else {makezero=true;start=start->get_cdr();}// if not monotonically increasing,return 0
	    }
	    if (makezero==true) return make_int(0);
	    return make_int(1);
	 }
}

Cell* neg(Cell* o)
{
            if(operand_num(o)!=1) throw runtime_error("There must be exactly one operand for NOT");
            else {
            Cell* cell=eval(o->get_car());
            if(cell==nil)
            return make_int(0);
            else 
            {
               if(cell->if_operation()) return make_int(0);
               else return make_int(1);
            }
         }
}

Cell* print(Cell* o)
{
   	    if(operand_num(o)!=1) throw runtime_error("There must be exactly one operand for PRINT");
            else {Cell* cell=eval(o->get_car());
            if(cell==nil) cout<<"()"<<endl;
            else {
                 cell->print();
                 cout<<endl;}
            return nil;}
}

//Cell* eval (Cell* o){}




Cell* eval(Cell* const c)
{
   symbol_table["ceiling"]=make_symbol("ceiling");
symbol_table["floor"]=make_symbol("floor");
symbol_table["if"]=make_symbol("if");
symbol_table["+"]=make_symbol("+");
symbol_table["*"]=make_symbol("*");
symbol_table["-"]=make_symbol("-");
symbol_table["/"]=make_symbol("/");
symbol_table["quote"]=make_symbol("quote");
symbol_table["cons"]=make_symbol("cons");
symbol_table["car"]=make_symbol("car");
symbol_table["cdr"]=make_symbol("cdr");
symbol_table["nullp"]=make_symbol("nullp");
symbol_table["intp"]=make_symbol("intp");
symbol_table["doublep"]=make_symbol("doublep");
symbol_table["symbolp"]=make_symbol("symbolp");
symbol_table["listp"]=make_symbol("listp");
//symbol_table["procedurep"]=make_symbol("procedurep");
symbol_table["define"]=make_symbol("define");
symbol_table["<"]=make_symbol("<");
symbol_table["not"]=make_symbol("not");
symbol_table["print"]=make_symbol("print");
symbol_table["eval"]=make_symbol("eval");
symbol_table["lambda"]=make_symbol("lambda");
symbol_table["apply"]=make_symbol("apply");
symbol_table["let"]=make_symbol("let");

   if (nullp(c)){throw runtime_error("Input is Nil");} //
   //if(eval(c->get_car())->is_operator())cout<<"hahah";
   else if(listp(c))
   {//cout << eval(c->get_car())->is_procedure() << endl;
     if(eval(c->get_car())==nil) throw runtime_error("Input is Nil");
     else if(eval(c->get_car())->is_operator()) 
     {
      
      if(eval(c->get_car())->get_symbol()=="ceiling")
      {
	 return ceiling(c->get_cdr());
      }

      else if(eval(c->get_car())->get_symbol()=="floor")
      {
	 return floor(c->get_cdr());
      }

      else if(eval(c->get_car())->get_symbol()=="if")
      {
	 if(operand_num(c)<=2||operand_num(c)>=5)
	 {throw runtime_error("The operand number of IF should be 3 or 4");}//Check whether the operand number is valid 
	 else {
	    //if the first operand is nonzero return the second operand
	    Cell* result=eval(c->get_cdr()->get_car());
            if(result==nil||result->if_operation())
            {return eval(c->get_cdr()->get_cdr()->get_car());}
            //if the first operand is zero return the third operand
	    else {
	       if(operand_num(c)==3) return make_int(0);//unspecified In this program, return 0
	       else return eval(c->get_cdr()->get_cdr()->get_cdr()->get_car());
	    }
	 }
      }

      else if(eval(c->get_car())->get_symbol()=="+")
      {
         return addition(c->get_cdr());
      }

      else if(eval(c->get_car())->get_symbol()=="*")
      {
         return multiplication(c->get_cdr());
      }
      
      else if(eval(c->get_car())->get_symbol()=="-")
      {
	 return subtraction(c->get_cdr());
      }
      
      else if(eval(c->get_car())->get_symbol()=="/")
      {
	 return division(c->get_cdr());
      }
      
      else if(eval(c->get_car())->get_symbol()=="quote")
      {
         if(operand_num(c)==1||operand_num(c)>=3) //Check whether the operand number is valid 
         {
            throw runtime_error("There must be exactly one operand for QUOTE");
         }
         else return c->get_cdr()->get_car();
      }

      //////////////////////////////////////////////////////////////////////////
      else if(eval(c->get_car())->get_symbol()=="cons")
      {
         if(operand_num(c)!=3)
         {
            throw runtime_error("There must be exactly two operand for CONS");
         }
         Cell* car=eval(c->get_cdr()->get_car());
         Cell* cdr=eval(c->get_cdr()->get_cdr()->get_car());
         if(cdr==nil) return cons(car,cdr);
         else if(cdr->is_cons()) return cons(car,cdr);
	 else {throw runtime_error("There must be an end");}
      }

      else if(eval(c->get_car())->get_symbol()=="car")
      {
         if(operand_num(c)!=2)
         {
            throw runtime_error("There must be exactly one operand for CAR");
         }
         Cell* cell=eval(c->get_cdr()->get_car());
         if(cell==nil)
         {
            throw runtime_error("Invalid operand for CAR");
         }
         else if (c->get_cdr()->is_cons())return cell->get_car();
         else 
         {
            throw runtime_error("Invalid operand for CAR");
         }
      }

      else if(eval(c->get_car())->get_symbol()=="cdr")
      {
         if(operand_num(c)!=2)
         {
            throw runtime_error("There must be exactly one operand for CDR");
         }
         Cell* cell=eval(c->get_cdr()->get_car());
         if(cell==nil)
         {
            throw runtime_error("Invalid operand for CDR");
         }
         else if (cell->is_cons())return cell->get_cdr();
         else 
         {
            throw runtime_error("Invalid operand for CDR");
         }
         
      }

      else if(eval(c->get_car())->get_symbol()=="nullp")
      {
         if(operand_num(c)!=2)
         {
           throw runtime_error("There must be exactly one operand for NULLP");
         }
         else {
            Cell* cell=eval(c->get_cdr()->get_car());
            int null=nullp(cell);return make_int(null);}
      }
      
      else if(eval(c->get_car())->get_symbol()=="intp")
      {
         if(operand_num(c)!=2)
         {
           throw runtime_error("There must be exactly one operand for INTP");
         }
         else {
            Cell* cell=eval(c->get_cdr()->get_car());
            int int_=intp(cell);return make_int(int_);}
      }
      
      else if(eval(c->get_car())->get_symbol()=="doublep")
      {
         if(operand_num(c)!=2)
         {
           throw runtime_error("There must be exactly one operand for DOUBLEP");
         }
         else {
            Cell* cell=eval(c->get_cdr()->get_car());
            int double_=doublep(cell);return make_int(double_);}
      }
      
      else if(eval(c->get_car())->get_symbol()=="listp")
      {
         if(operand_num(c)!=2)
         {
           throw runtime_error("There must be exactly one operand for LISTP");
         }
         else {
            Cell* cell=eval(c->get_cdr()->get_car());
            int list=listp(cell);return make_int(list);}
      }
      
      else if(eval(c->get_car())->get_symbol()=="symbolp")
      {
         if(operand_num(c)!=2)
         {
           throw runtime_error("There must be exactly one operand for SYMBOLP");
         }
         else {
            Cell* cell=eval(c->get_cdr()->get_car());
            int symbol=symbolp(cell);return make_int(symbol);}
      }

      


      
      else if(eval(c->get_car())->get_symbol()=="define")
      {
         if(operand_num(c)!=3) /////////operand number
         throw runtime_error("There must be exactly two operand for DEFINE");
         if(!c->get_cdr()->get_car()->is_symbol()) 
         throw runtime_error("The first operand must be a SymbolCell");
         else {
	    if(c->get_cdr()->get_car()->is_operator()) throw runtime_error("Built-in operator protected");
            else if(symbol_table.find(c->get_cdr()->get_car()->get_symbol())!=symbol_table.end()) 
            throw runtime_error("The symbol is already defined"); //check if the symbol has already been defined 
            else {
                Cell* result=eval(c->get_cdr()->get_cdr()->get_car()); 
                symbol_table[c->get_cdr()->get_car()->get_symbol()]=result;
            }
         }
         return nil;
      }
      
      else if(eval(c->get_car())->get_symbol()=="<")
      {
	   return smaller(c->get_cdr());
      }
      
      else if(eval(c->get_car())->get_symbol()=="not")
      {
	   return neg(c->get_cdr());
      }
      
      else if(eval(c->get_car())->get_symbol()=="print")
      {
         return print(c->get_cdr()); 
      }
      
      else if(eval(c->get_car())->get_symbol()=="eval")
      {
         if(operand_num(c)!=2) throw runtime_error("There must be exactly one operand for EVAL");
         else return eval(eval(c->get_cdr()->get_car()));
      }
      
      else if(eval(c->get_car())->get_symbol()=="lambda")
      {/////////operand number
         if(operand_num(c)<3) throw runtime_error("There must be at least two operands for LAMBDA");
         else {
            /*Cell* cur=c->get_cdr()->get_cdr();
            while(cur!=nil)
            {
               if(cur->get_car()==nil ||!listp(cur->get_car())) throw runtime_error("Invalid procedure body");
               else cur=cur->get_cdr();
            }*/
            if(listp(c->get_cdr()->get_car()))//check whether the formals is valid
            {
               if(c->get_cdr()->get_car()==nil) return lambda(c->get_cdr()->get_car(),c->get_cdr()->get_cdr());
               else if(c->get_cdr()->get_car()->is_cons())
               {
                  Cell* cur=c->get_cdr()->get_car();
                  while (cur!=nil)
                  {
                     if(!(cur->get_car()->is_symbol())) throw runtime_error("Invalid procedure formals");
                     cur=cur->get_cdr(); 
                  }
                  map<string,Cell*> arg_map;
                  cur=c->get_cdr()->get_car();
                  while (cur!=nil)//check if there repeated parameter
                  {
                     if(arg_map.find(cur->get_car()->get_symbol())==arg_map.end())
                     {
                        arg_map[cur->get_car()->get_symbol()]=make_int(0);//cur->get_car()->print();
                        cur=cur->get_cdr();
                     }
                     else throw runtime_error("Can't accepted repeated arguments");
                  }
                  
               }
            }
            else if(symbolp(c->get_cdr()->get_car()))
            {throw runtime_error("under construction");}
            //lambda(c->get_cdr()->get_car(),c->get_cdr()->get_cdr())->get_formals()->print();
            return lambda(c->get_cdr()->get_car(),c->get_cdr()->get_cdr());
         }
      }
      
      else if(eval(c->get_car())->get_symbol()=="apply")
      {
         Cell* cell=eval(c->get_cdr()->get_car()); 
         if(operand_num(c)!=3) throw runtime_error("There must be exactly three operands for APPLY");
         else {
            if(cell==nil) throw runtime_error("Can't apply a nil procedure");
            else if(cell->is_procedure())
            return cell->apply(eval(c->get_cdr()->get_cdr()->get_car())) ;
            else if(cell->procedure_built_in())//apply to a built in operator
            {
               if(cell->get_symbol()=="+")
               {
                  return addition(eval(c->get_cdr()->get_cdr()->get_car()));
               }
               else if(cell->get_symbol()=="-")
               {
                  return subtraction(eval(c->get_cdr()->get_cdr()->get_car()));
               }
               else if(cell->get_symbol()=="*")
               {
                  return multiplication(eval(c->get_cdr()->get_cdr()->get_car()));
               }
               else if(cell->get_symbol()=="/")
               {
                  return division(eval(c->get_cdr()->get_cdr()->get_car()));
               }
               else if(cell->get_symbol()=="floor")
               {
                  return floor(eval(c->get_cdr()->get_cdr()->get_car()));
               }
               else if(cell->get_symbol()=="ceiling")
               {
                  return ceiling(eval(c->get_cdr()->get_cdr()->get_car()));
               }
               else if(cell->get_symbol()=="not")
               {
                  return neg(eval(c->get_cdr()->get_cdr()->get_car()));
               }
               else if(cell->get_symbol()=="<")
               {
                  return smaller(eval(c->get_cdr()->get_cdr()->get_car()));
               }
               else if(cell->get_symbol()=="print")
               {
                  return print(eval(c->get_cdr()->get_cdr()->get_car()));
               }
               else {throw runtime_error("under construction");}
 
            }
            else throw runtime_error("No valid procedure");
         }
      }
      
      else if(eval(c->get_car())->get_symbol()=="let")
      {
         if(operand_num(c)!=3) throw runtime_error("There must be at least two operands for LET");

            if(c->get_cdr()->get_car()==nil)//if no arguments are passed
            {
               return eval(c->get_cdr()->get_cdr()->get_car());
            }
            else if(c->get_cdr()->get_car()->is_cons())
            {
               map<string,Cell*> arg_map;
               Cell* cur=c->get_cdr()->get_car();
               while(cur!=nil) //the format of the arguments list must be(symbol,xx)
               { 
                  if(cur->get_car()==nil || !cur->get_car()->is_cons()) 
                  throw runtime_error("Invalid arguments list, should be a list");
                  else if(cur->get_car()->is_cons())
                  {  
                     if(operand_num(cur->get_car())!=2)
                     {throw runtime_error("Only allowed to initialize a symbol once");}
                     if(cur->get_car()->get_car()==nil || ! cur->get_car()->get_car()->is_symbol())
                     {throw runtime_error("Invalid arguments list, should be a symbol");}//cur->get_car()->print(); 
                     if(arg_map.find(cur->get_car()->get_car()->get_symbol())==arg_map.end())
                     {
                        arg_map[cur->get_car()->get_car()->get_symbol()]=eval(cur->get_car()->get_cdr()->get_car());
                        cur=cur->get_cdr();
                     }
                     else if(arg_map.find(cur->get_car()->get_car()->get_symbol())!=arg_map.end())
                     {map_list.pop_front();throw runtime_error("Can't accepted repeated arguments");}
                  }
               }
               map_list.push_front(arg_map);
               Cell*result=eval(c->get_cdr()->get_cdr()->get_car());
               map_list.pop_front();
               return result;
            }
            else throw runtime_error("Invalid arguments list");
      }
    }

      
    else if(eval(c->get_car())->is_procedure())//not including built-in types
    {
       //cout<<"help"<<endl;
       return eval(c->get_car())->apply(c->get_cdr());
    }
    
    else 
    {throw runtime_error("No valid operator");}//if no valid operator is taken, exit

   }
   //(if (not (nullp (quote()))) (apply sq (cons (car (quote())) (quote ()))))

   else if(symbolp(c))
   {
      list< map<string,Cell*> >::iterator it;
      it=map_list.begin();
      while (it!=map_list.end())
      {
         if (it->find(c->get_symbol())==it->end())
         it++;
         else return it->find(c->get_symbol())->second;
      }
      if(symbol_table.find(c->get_symbol())==symbol_table.end()) 
      throw runtime_error("It's an undefined symbol");
      else return symbol_table.find(c->get_symbol())->second;
   }
   //
   else return c;
}//
/*
(define for-each (lambda (x y) (if (not (nullp y)) (apply x (cons (car y) (quote ())))) (if (not (nullp (cdr y))) (for-each x (cdr y)  ))(quote())))
(define for-each (lambda (x y) (apply x (quote (car y))) (if (not (nullp y)) (for_each x (cdr y)))))*/
