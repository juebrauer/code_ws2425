#include <iostream>
#include <concepts>

#include <stdlib.h>


template <typename T>
requires std::is_arithmetic_v<T>
class hkevector
{
    public:

        hkevector(unsigned int capacity)
        {
            this->capacity = capacity;

            data = (T*) malloc(capacity * sizeof(T));
            nr_elements = 0;
        }

        ~hkevector()
        {
            free(data);
        }

        void push_back(T x)
        {
            // Is the data buffer already full?
            if (nr_elements == capacity)
            {
                // Make the data buffer larger
                capacity++;
                data = (T*)realloc(data, capacity * sizeof(T));
            }
            data[nr_elements++] = x;
        }

        void print()
        {
            std::cout << "len=" << nr_elements << " : ";
            for (int i=0; i<nr_elements; i++)
                std::cout << data[i] << " ";
            std::cout << std::endl;
        }


        bool remove_value(T value)
        /*
            i  data[i]
            0  5
            1  9
            2  2
            3  10
            4  <new_value>
            5  11
            6  12
            7  13
            8  14
            9  15
        */
        {
            // 1. Try to find the specified value in the data buffer
            bool found = false;
            int i;
            for (i=0; i<nr_elements; i++)
            {
                if (data[i] == value)
                {
                    found = true;
                    break;
                }
            }

            if (found)
                remove_index(i);

            return found;
        }


        bool remove_all_values(T value)
        {
            bool found = false;
            while (remove_value(value))
            {
                found = true;
            };
            return found;    
        }



        bool remove_index(int idx)
        {
            // 1. Make sure, the index is valid
            if ((idx<0) || (idx>=nr_elements))
                return false;

            // 2. Move all elements starting from index position i+1
            //    in the data buffer to each previous index position
            for (int j=idx; j<nr_elements-1; j++)
            {
                data[j] = data[j+1];         
            }
            nr_elements--;
            return true;
        }


        void insert(int idx, T value)
        {
            // 1. Index überprüfen
            if (idx < 0 || idx > nr_elements)
            {
                std::cerr << "Index out of range!" << std::endl;
                return;
            }

            // 2. Wenn der Speicher voll ist, Kapazität erhöhen
            if (nr_elements == capacity)
            {
                capacity++;
                data = (T*)realloc(data, capacity * sizeof(T));
            }

            // 3. Elemente nach rechts verschieben
            for (int j = nr_elements; j > idx; j--)
            {
                data[j] = data[j - 1];
            }

            // 4. Neues Element einfügen
            data[idx] = value;
            nr_elements++;
        }



        


    private:
        T*   data;
        int  capacity;
        int  nr_elements;


};

template <typename T>
T square(T x)
{
    return x*x;
}



int main()
{
    std::cout << square(5) << std::endl;
    std::cout << square(5.9) << std::endl;


    //hkevector<std::string*> my_vector2(5);

    hkevector<double> my_vector(3);

    my_vector.push_back(5.5);
    my_vector.push_back(9);
    my_vector.push_back(2.3);
    my_vector.push_back(10);
    for (int i=10; i<=15; i++)
        my_vector.push_back(i);
    my_vector.push_back(10);

    my_vector.print();
    my_vector.insert(3, 99.9);
    my_vector.remove_value(2.3);

    
    my_vector.print();

}