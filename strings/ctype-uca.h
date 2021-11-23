#ifndef CTYPE_UCA_H
#define CTYPE_UCA_H
/* Copyright (c) 2021, MariaDB

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; version 2
   of the License.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the Free
   Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
   MA 02110-1335  USA */

typedef struct my_uca_implict_weight_t
{
  uint16 weight[2];
} MY_UCA_IMPLICIT_WEIGHT;


static inline MY_UCA_IMPLICIT_WEIGHT
my_uca_implicit_weight_primary_default(uint16 base, my_wc_t code)
{
  MY_UCA_IMPLICIT_WEIGHT res;
  res.weight[0]= (uint16) ((code >> 15) + base);
  res.weight[1]= (uint16) ((code & 0x7FFF)|0x8000);
  return res;
}


static inline MY_UCA_IMPLICIT_WEIGHT
my_uca_520_implicit_weight_primary(my_wc_t code)
{
  uint16 base;
  /*
  3400;<CJK Ideograph Extension A, First>
  4DB5;<CJK Ideograph Extension A, Last>
  4E00;<CJK Ideograph, First>
  9FA5;<CJK Ideograph, Last>
  */
  if (code >= 0x3400 && code <= 0x4DB5)
    base= 0xFB80;
  else if (code >= 0x4E00 && code <= 0x9FA5)
    base= 0xFB40;
  else
    base= 0xFBC0;

  return my_uca_implicit_weight_primary_default(base, code);
}


static inline MY_UCA_IMPLICIT_WEIGHT
my_uca_implicit_weight_secondary()
{
  MY_UCA_IMPLICIT_WEIGHT res;
  res.weight[0]= 0x0020;
  res.weight[1]= 0;
  return res;
}


static inline MY_UCA_IMPLICIT_WEIGHT
my_uca_implicit_weight_tertiary()
{
  MY_UCA_IMPLICIT_WEIGHT res;
  res.weight[0]= 0x0002;
  res.weight[1]= 0;
  return res;
}


static inline MY_UCA_IMPLICIT_WEIGHT
my_uca_implicit_weight_quaternary()
{
  MY_UCA_IMPLICIT_WEIGHT res;
  res.weight[0]= 0x0001;
  res.weight[1]= 0;
  return res;
}


static inline MY_UCA_IMPLICIT_WEIGHT
my_uca_520_implicit_weight_on_level(my_wc_t code, uint level)
{
  switch (level) {
  case 0:
    return my_uca_520_implicit_weight_primary(code);
  case 1:
    return my_uca_implicit_weight_secondary();
  case 2:
    return my_uca_implicit_weight_tertiary();
  default:
    break;
  }
  return my_uca_implicit_weight_quaternary();
}


#endif /* CTYPE_UCA_H */
