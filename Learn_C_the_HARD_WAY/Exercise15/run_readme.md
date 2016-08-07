##指针小知识


> * type *ptr

> type 类型的指针，名为 ptr 。

> * *ptr

> ptr 所指向位置的值。

> * *(ptr + i)

> （ptr 所指向位置加上 i ） 的值。

> 译者注：以字节为单位的话，应该是 ptr 所指向的位置再加上 sizeof(type) * i 。

> * &thing

> thing 的地址。

> * type *ptr = &thing

> 名为 ptr ， type 类型的指针，值设置为 thing 的地址。

> * ptr++

> 自增 ptr 指向的位置


> * 除了 sizeof 、 & 操作和声明之外，数组名称都会被编译器推导为
指向其首个元素的指针。对于这些情况，不要用“是”这个词，而是要用“推导”。