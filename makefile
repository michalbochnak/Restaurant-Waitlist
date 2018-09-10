wait_list: user_interface.o linked_list.o linked_list_impl.o
	gcc -o wait_list user_interface.o linked_list.o linked_list_impl.o

user_interface.o: user_interface.c wait_list.h
	gcc -c user_interface.c

linked_list.o: linked_list.c wait_list.h
	gcc -c linked_list.c

linked_list_impl.o: linked_list_impl.c wait_list.h
	gcc -c linked_list_impl.c

clean:
	rm user_interface.o linked_list.o linked_list_impl.o
