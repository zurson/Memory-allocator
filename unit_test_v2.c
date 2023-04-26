/*
 * Unit Test Bootstrap
 * Autor: Tomasz Jaworski, 2018-2020
 *
 * Test dla zadania Projekt: Ocena 3,0
 * Autor testowanej odpowiedzi: Mateusz Jurek
 * Test wygenerowano automatycznie o 2022-12-11 14:00:02.418033
 *
 * Debug: 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <setjmp.h>
#include <assert.h>

#if !defined(__clang__) && !defined(__GNUC__)
// Zakomentuj poniższy błąd, jeżeli chcesz przetestować testy na swoim kompilatorze C.
#error System testow jednostkowych jest przeznaczony dla kompilatorów GCC/Clang.
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
// Zakomentuj poniższy błąd, jeżeli chcesz przetestować testy na platformie Windows.
#error System testow jednostkowych NIE jest przeznaczony dla testów uruchamianych na platformach Windows.
#endif

#define _RLDEBUG_API_
#include "unit_helper_v2.h"
#include "rdebug.h"

#include "tested_declarations.h"
#include "rdebug.h"

//
// Elementy globalne dla całego testu
//




//
//  Test 1: Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej wartości 0
//
void UTEST1(void)
{
    // informacje o teście
    test_start(1, "Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej wartości 0", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);
                
                void *ptr = heap_malloc(0);
                
                test_error(ptr == NULL, "Funkcja heap_malloc() powinna zwrócić wartość NULL");

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 2: Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń obecna na stercie
//
void UTEST2(void)
{
    // informacje o teście
    test_start(2, "Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń obecna na stercie", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr = heap_malloc(67108831);

                test_error(ptr == NULL, "Funkcja heap_malloc() powinna zwrócić wartość NULL");

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 3: Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku pierwszej próby zaalokowania przestrzeni mniejszej niż przestrzeń obecna na stercie
//
void UTEST3(void)
{
    // informacje o teście
    test_start(3, "Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku pierwszej próby zaalokowania przestrzeni mniejszej niż przestrzeń obecna na stercie", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr = heap_malloc(790);

                test_error(ptr != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                heap_clean();
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 4: Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni mniejszej niż przestrzeń obecna na stercie, w przypadku przydzielenia wcześniej pamięci użytkownikowi
//
void UTEST4(void)
{
    // informacje o teście
    test_start(4, "Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni mniejszej niż przestrzeń obecna na stercie, w przypadku przydzielenia wcześniej pamięci użytkownikowi", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr1 = heap_malloc(98);
                test_error(ptr1 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));
                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr2 = heap_malloc(141);
                test_error(ptr2 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr2));
                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                heap_clean();
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 5: Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni mniejszej niż przestrzeń obecna na stercie (żądana pamięć wymaga zwiększenia limitu pamięci przydzielonego przez system), w przypadku przydzielenia wcześniej pamięci użytkownikowi
//
void UTEST5(void)
{
    // informacje o teście
    test_start(5, "Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni mniejszej niż przestrzeń obecna na stercie (żądana pamięć wymaga zwiększenia limitu pamięci przydzielonego przez system), w przypadku przydzielenia wcześniej pamięci użytkownikowi", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr1 = heap_malloc(87);
                test_error(ptr1 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));
                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr2 = heap_malloc(15024122);
                test_error(ptr2 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr2));
                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 6: Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń, która może być przydzielona przez system (żądana pamięć wymaga zwiększenia limitu pamięci przydzielonego przez system), w przypadku przydzielenia wcześniej pamięci użytkownikowi
//
void UTEST6(void)
{
    // informacje o teście
    test_start(6, "Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń, która może być przydzielona przez system (żądana pamięć wymaga zwiększenia limitu pamięci przydzielonego przez system), w przypadku przydzielenia wcześniej pamięci użytkownikowi", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr1 = heap_malloc(65);
                test_error(ptr1 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));
                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr2 = heap_malloc(67761462);
                test_error(ptr2 == NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 7: Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeń mniejszej niż przestrzeń poprzednio zwolniona
//
void UTEST7(void)
{
    // informacje o teście
    test_start(7, "Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeń mniejszej niż przestrzeń poprzednio zwolniona", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr1 = heap_malloc(72);
                void *ptr2 = heap_malloc(176);
                void *ptr3 = heap_malloc(200);

                test_error(ptr1 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(ptr2 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(ptr3 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");

                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));
                test_error(pointer_valid == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr2));
                test_error(pointer_valid == get_pointer_type(ptr3), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr3));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                heap_free(ptr2);

                test_error(pointer_unallocated == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr2));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr4 = heap_malloc(162);
                test_error(ptr2 == ptr4, "Funkcja heap_malloc() powinna zwrócić adres równy adresowi ptr2 (jest możliwość wykorzystania wolnego bloku pamięci do zaalokowania), a zwróciła różny");

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 8: Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni równej przestrzeni poprzednio zwolnionej
//
void UTEST8(void)
{
    // informacje o teście
    test_start(8, "Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni równej przestrzeni poprzednio zwolnionej", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr1 = heap_malloc(18);
                void *ptr2 = heap_malloc(129);
                void *ptr3 = heap_malloc(226);

                test_error(ptr1 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(ptr2 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(ptr3 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");

                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));
                test_error(pointer_valid == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr2));
                test_error(pointer_valid == get_pointer_type(ptr3), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr3));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                heap_free(ptr2);

                test_error(pointer_unallocated == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr2));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr4 = heap_malloc(129);
                test_error(ptr2 == ptr4, "Funkcja heap_malloc() powinna zwrócić adres równy adresowi ptr2 (jest możliwość wykorzystania wolnego bloku pamięci do zaalokowania), a zwróciła różny");

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 9: Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni mniejszej niż przestrzeń poprzednio zwolniona
//
void UTEST9(void)
{
    // informacje o teście
    test_start(9, "Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni mniejszej niż przestrzeń poprzednio zwolniona", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                size_t mem_sizes[] = {538, 904, 164, 187, 409, 732, 572, 453, 655, 952, 373, 329, 431, 204, 171, 125, 107, 814, 103, 941, 977, 595, 782, 508, 926, 629, 683, 239, 399, 609};
                void *ptrs[30];

                for (int i = 0; i < 30; ++i)
                {
                    ptrs[i] = heap_malloc(mem_sizes[i]);
                    test_error(ptrs[i] != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                    test_error(pointer_valid == get_pointer_type(ptrs[i]), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptrs[i]));

                    status = heap_validate();
                    test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                }           

                heap_free(ptrs[5]);

                test_error(pointer_unallocated == get_pointer_type(ptrs[5]), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptrs[5]));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr = heap_malloc(712);
                test_error(ptrs[5] == ptr, "Funkcja heap_malloc() powinna zwrócić adres równy adresowi ptrs[5] (jest możliwość wykorzystania wolnego bloku pamięci do zaalokowania), a zwróciła różny");

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 10: Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni równej przestrzeń poprzednio zwolnionej
//
void UTEST10(void)
{
    // informacje o teście
    test_start(10, "Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni równej przestrzeń poprzednio zwolnionej", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                size_t mem_sizes[] = {612, 417, 651, 439, 220, 849, 283, 725, 127, 477, 408, 655, 177, 590, 768, 556, 952, 597, 908, 967, 550, 471, 714, 676, 216, 672, 543, 805, 603, 375, 359, 239, 788, 278, 742, 360};
                void *ptrs[36];

                for (int i = 0; i < 36; ++i)
                {
                    ptrs[i] = heap_malloc(mem_sizes[i]);
                    test_error(ptrs[i] != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                    test_error(pointer_valid == get_pointer_type(ptrs[i]), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptrs[i]));

                    status = heap_validate();
                    test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                }           

                heap_free(ptrs[10]);

                test_error(pointer_unallocated == get_pointer_type(ptrs[10]), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptrs[10]));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr = heap_malloc(408);
                test_error(ptrs[10] == ptr, "Funkcja heap_malloc() powinna zwrócić adres równy adresowi ptrs[10] (jest możliwość wykorzystania wolnego bloku pamięci do zaalokowania), a zwróciła różny");

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 11: Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń poprzednio zwolnionej
//
void UTEST11(void)
{
    // informacje o teście
    test_start(11, "Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń poprzednio zwolnionej", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr1 = heap_malloc(100);
                void *ptr2 = heap_malloc(160);
                void *ptr3 = heap_malloc(215);

                test_error(ptr1 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(ptr2 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(ptr3 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");

                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));
                test_error(pointer_valid == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr2));
                test_error(pointer_valid == get_pointer_type(ptr3), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr3));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                heap_free(ptr2);

                test_error(pointer_unallocated == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr2));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr4 = heap_malloc(170);
                
                test_error(ptr2 != ptr4, "Funkcja heap_malloc() powinna zwrócić adres równy adresowi ptr2 (jest możliwość wykorzystania wolnego bloku pamięci do zaalokowania), a zwróciła różny");
                test_error(ptr4 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr4), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr4));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 12: Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń poprzednio zwolnionej
//
void UTEST12(void)
{
    // informacje o teście
    test_start(12, "Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń poprzednio zwolnionej", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr1 = heap_malloc(83);
                void *ptr2 = heap_malloc(6);
                void *ptr3 = heap_malloc(203);

                test_error(ptr1 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(ptr2 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(ptr3 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");

                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));
                test_error(pointer_valid == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr2));
                test_error(pointer_valid == get_pointer_type(ptr3), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr3));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                heap_free(ptr2);

                test_error(pointer_unallocated == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr2));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr4 = heap_malloc(16);

                test_error(ptr2 != ptr4, "Funkcja heap_malloc() powinna zwrócić adres równy adresowi ptr2 (jest możliwość wykorzystania wolnego bloku pamięci do zaalokowania), a zwróciła różny");
                test_error(ptr4 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr4), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr4));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 13: Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej wartości 0
//
void UTEST13(void)
{
    // informacje o teście
    test_start(13, "Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej wartości 0", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr = heap_calloc(0, 0);

                test_error(ptr == NULL, "Funkcja heap_calloc() powinna zwrócić wartość NULL");

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 14: Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej wartości 0
//
void UTEST14(void)
{
    // informacje o teście
    test_start(14, "Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej wartości 0", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr = heap_calloc(74, 0);

                test_error(ptr == NULL, "Funkcja heap_calloc() powinna zwrócić wartość NULL");

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 15: Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej wartości 0
//
void UTEST15(void)
{
    // informacje o teście
    test_start(15, "Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej wartości 0", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr = heap_calloc(0, 2);

                test_error(ptr == NULL, "Funkcja heap_calloc() powinna zwrócić wartość NULL");

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 16: Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń obecna na stercie
//
void UTEST16(void)
{
    // informacje o teście
    test_start(16, "Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń obecna na stercie", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr = heap_calloc(67108829, 1);

                test_error(ptr == NULL, "Funkcja heap_calloc() powinna zwrócić wartość NULL");

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 17: Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń obecna na stercie
//
void UTEST17(void)
{
    // informacje o teście
    test_start(17, "Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń obecna na stercie", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr = heap_calloc(16777213, 4);

                test_error(ptr == NULL, "Funkcja heap_calloc() powinna zwrócić wartość NULL");

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 18: Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku pierwszej próby zaalokowania przestrzeni mniejszej niż przestrzeń obecna na stercie
//
void UTEST18(void)
{
    // informacje o teście
    test_start(18, "Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku pierwszej próby zaalokowania przestrzeni mniejszej niż przestrzeń obecna na stercie", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr = heap_calloc(351, 1);

                test_error(ptr != NULL, "Funkcja heap_calloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr), "Funkcja heap_calloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr));

                for (int i = 0; i < 351; ++i)
                    test_error(ptr[i] == 0, "Funkcja heap_calloc() powinna zwrócić wskaźnik na obszar pamięci wypełniony wartościami 0");


                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 19: Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku pierwszej próby zaalokowania przestrzeni mniejszej niż przestrzeń obecna na stercie
//
void UTEST19(void)
{
    // informacje o teście
    test_start(19, "Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku pierwszej próby zaalokowania przestrzeni mniejszej niż przestrzeń obecna na stercie", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr = heap_calloc(212, 16);

                test_error(ptr != NULL, "Funkcja heap_calloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr), "Funkcja heap_calloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr));

                for (int i = 0; i < 3392; ++i)
                    test_error(ptr[i] == 0, "Funkcja heap_calloc() powinna zwrócić wskaźnik na obszar pamięci wypełniony wartościami 0");


                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 20: Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni mniejszej niż przestrzeń obecna na stercie, w przypadku przydzielenia wcześniej pamięci użytkownikowi
//
void UTEST20(void)
{
    // informacje o teście
    test_start(20, "Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni mniejszej niż przestrzeń obecna na stercie, w przypadku przydzielenia wcześniej pamięci użytkownikowi", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr1 = heap_calloc(83, 48);
                test_error(ptr1 != NULL, "Funkcja heap_calloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_calloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));
                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                for (int i = 0; i < 3984; ++i)
                    test_error(ptr1[i] == 0, "Funkcja heap_calloc() powinna zwrócić wskaźnik na obszar pamięci wypełniony wartościami 0");

                char *ptr2 = heap_calloc(174, 48);
                test_error(ptr2 != NULL, "Funkcja heap_calloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr2), "Funkcja heap_calloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr2));
                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                for (int i = 0; i < 8352; ++i)
                    test_error(ptr2[i] == 0, "Funkcja heap_calloc() powinna zwrócić wskaźnik na obszar pamięci wypełniony wartościami 0");

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 21: Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni mniejszej niż przestrzeń obecna na stercie (żądana pamięć wymaga zwiększenia limitu pamięci przydzielonego przez system), w przypadku przydzielenia wcześniej pamięci użytkownikowi
//
void UTEST21(void)
{
    // informacje o teście
    test_start(21, "Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni mniejszej niż przestrzeń obecna na stercie (żądana pamięć wymaga zwiększenia limitu pamięci przydzielonego przez system), w przypadku przydzielenia wcześniej pamięci użytkownikowi", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr1 = heap_calloc(48, 3);
                test_error(ptr1 != NULL, "Funkcja heap_calloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_calloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));
                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                for (int i = 0; i < 144; ++i)
                    test_error(ptr1[i] == 0, "Funkcja heap_calloc() powinna zwrócić wskaźnik na obszar pamięci wypełniony wartościami 0");

                char *ptr2 = heap_calloc(13312794, 3);
                test_error(ptr2 != NULL, "Funkcja heap_calloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr2), "Funkcja heap_calloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr2));
                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                for (int i = 0; i < 39938382; ++i)
                    test_error(ptr2[i] == 0, "Funkcja heap_calloc() powinna zwrócić wskaźnik na obszar pamięci wypełniony wartościami 0");

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 22: Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń, która może być przydzielona przez system (żądana pamięć wymaga zwiększenia limitu pamięci przydzielonego przez system), w przypadku przydzielenia wcześniej pamięci użytkownikowi
//
void UTEST22(void)
{
    // informacje o teście
    test_start(22, "Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń, która może być przydzielona przez system (żądana pamięć wymaga zwiększenia limitu pamięci przydzielonego przez system), w przypadku przydzielenia wcześniej pamięci użytkownikowi", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr1 = heap_calloc(27, 2);
                test_error(ptr1 != NULL, "Funkcja heap_calloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_calloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));
                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                for (int i = 0; i < 54; ++i)
                    test_error(ptr1[i] == 0, "Funkcja heap_calloc() powinna zwrócić wskaźnik na obszar pamięci wypełniony wartościami 0");

                char *ptr2 = heap_calloc(67792240, 2);
                test_error(ptr2 == NULL, "Funkcja heap_calloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 23: Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeń mniejszej niż przestrzeń poprzednio zwolniona
//
void UTEST23(void)
{
    // informacje o teście
    test_start(23, "Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeń mniejszej niż przestrzeń poprzednio zwolniona", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr1 = heap_calloc(73, 1);
                char *ptr2 = heap_calloc(181, 1);
                char *ptr3 = heap_calloc(228, 1);

                test_error(ptr1 != NULL, "Funkcja heap_calloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(ptr2 != NULL, "Funkcja heap_calloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(ptr3 != NULL, "Funkcja heap_calloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");

                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_calloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));
                test_error(pointer_valid == get_pointer_type(ptr2), "Funkcja heap_calloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr2));
                test_error(pointer_valid == get_pointer_type(ptr3), "Funkcja heap_calloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr3));

                for (int i = 0; i < 73; ++i)
                    test_error(ptr1[i] == 0, "Funkcja heap_calloc() powinna zwrócić wskaźnik na obszar pamięci wypełniony wartościami 0");

                for (int i = 0; i < 181; ++i)
                    test_error(ptr2[i] == 0, "Funkcja heap_calloc() powinna zwrócić wskaźnik na obszar pamięci wypełniony wartościami 0");
     
                for (int i = 0; i < 228; ++i)
                    test_error(ptr3[i] == 0, "Funkcja heap_calloc() powinna zwrócić wskaźnik na obszar pamięci wypełniony wartościami 0");

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                heap_free(ptr2);

                test_error(pointer_unallocated == get_pointer_type(ptr2), "Funkcja heap_calloc() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr2));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr4 = heap_calloc(159, 1);
                test_error(ptr2 == ptr4, "Funkcja heap_calloc() powinna zwrócić adres równy adresowi ptr2 (jest możliwość wykorzystania wolnego bloku pamięci do zaalokowania), a zwróciła różny");

                for (int i = 0; i < 159; ++i)
                    test_error(ptr4[i] == 0, "Funkcja heap_calloc() powinna zwrócić wskaźnik na obszar pamięci wypełniony wartościami 0");

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 24: Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni równej przestrzeni poprzednio zwolnionej
//
void UTEST24(void)
{
    // informacje o teście
    test_start(24, "Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni równej przestrzeni poprzednio zwolnionej", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr1 = heap_calloc(65, 3);
                char *ptr2 = heap_calloc(178, 3);
                char *ptr3 = heap_calloc(277, 3);

                test_error(ptr1 != NULL, "Funkcja heap_calloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(ptr2 != NULL, "Funkcja heap_calloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(ptr3 != NULL, "Funkcja heap_calloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");

                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_calloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));
                test_error(pointer_valid == get_pointer_type(ptr2), "Funkcja heap_calloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr2));
                test_error(pointer_valid == get_pointer_type(ptr3), "Funkcja heap_calloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr3));

                for (int i = 0; i < 195; ++i)
                    test_error(ptr1[i] == 0, "Funkcja heap_calloc() powinna zwrócić wskaźnik na obszar pamięci wypełniony wartościami 0");

                for (int i = 0; i < 534; ++i)
                    test_error(ptr2[i] == 0, "Funkcja heap_calloc() powinna zwrócić wskaźnik na obszar pamięci wypełniony wartościami 0");
     
                for (int i = 0; i < 831; ++i)
                    test_error(ptr3[i] == 0, "Funkcja heap_calloc() powinna zwrócić wskaźnik na obszar pamięci wypełniony wartościami 0");

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                heap_free(ptr2);

                test_error(pointer_unallocated == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr2));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr4 = heap_calloc(178, 3);
                test_error(ptr2 == ptr4, "Funkcja heap_calloc() powinna zwrócić adres równy adresowi ptr2 (jest możliwość wykorzystania wolnego bloku pamięci do zaalokowania), a zwróciła różny");

                for (int i = 0; i < 534; ++i)
                    test_error(ptr4[i] == 0, "Funkcja heap_calloc() powinna zwrócić wskaźnik na obszar pamięci wypełniony wartościami 0");

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 25: Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni mniejszej niż przestrzeń poprzednio zwolniona
//
void UTEST25(void)
{
    // informacje o teście
    test_start(25, "Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni mniejszej niż przestrzeń poprzednio zwolniona", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                size_t mem_sizes[] = {648, 684, 458, 157, 944, 166, 202, 535, 840, 424, 104, 389, 761, 100, 310, 142, 679, 833, 915, 841, 663};
                size_t mem_units[] = {4, 3, 4, 2, 5, 5, 2, 4, 3, 2, 5, 1, 5, 5, 5, 3, 4, 3, 1, 1, 2};
                char *ptrs[21];

                for (int i = 0; i < 21; ++i)
                {
                    ptrs[i] = heap_calloc(mem_sizes[i], mem_units[i]);
                    test_error(ptrs[i] != NULL, "Funkcja heap_calloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                    test_error(pointer_valid == get_pointer_type(ptrs[i]), "Funkcja heap_calloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptrs[i]));

                    for (size_t j = 0; j < mem_sizes[i] * mem_units[i]; ++j)
                        test_error(ptrs[i][j] == 0, "Funkcja heap_calloc() powinna zwrócić wskaźnik na obszar pamięci wypełniony wartościami 0");

                    status = heap_validate();
                    test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                }

                heap_free(ptrs[14]);

                test_error(pointer_unallocated == get_pointer_type(ptrs[14]), "Funkcja heap_calloc() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptrs[14]));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr = heap_calloc(300, 5);
                test_error(ptrs[14] == ptr, "Funkcja heap_calloc() powinna zwrócić adres równy adresowi ptrs[14] (jest możliwość wykorzystania wolnego bloku pamięci do zaalokowania), a zwróciła różny");

                for (size_t j = 0; j < 300 * 5; ++j)
                    test_error(ptrs[14][j] == 0, "Funkcja heap_calloc() powinna zwrócić wskaźnik na obszar pamięci wypełniony wartościami 0");


                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
             
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 26: Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni równej przestrzeni poprzednio zwolnionej
//
void UTEST26(void)
{
    // informacje o teście
    test_start(26, "Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni równej przestrzeni poprzednio zwolnionej", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                 int status = heap_setup();
                 test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 size_t mem_sizes[] = {638, 667, 581, 705, 181, 762, 749, 780, 962, 685, 388, 793, 591, 165, 190, 877, 304, 935, 143, 422, 465, 662, 242, 361, 401, 211, 858, 777, 910, 266, 740, 589, 506};
                 size_t mem_units[] = {2, 1, 4, 3, 4, 3, 4, 5, 3, 5, 5, 3, 3, 4, 5, 5, 2, 5, 5, 4, 2, 3, 4, 1, 3, 4, 3, 2, 5, 4, 5, 5, 1};
                 char *ptrs[33];

                 for (int i = 0; i < 33; ++i)
                 {
                     ptrs[i] = heap_calloc(mem_sizes[i], mem_units[i]);
                     test_error(ptrs[i] != NULL, "Funkcja heap_calloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                     test_error(pointer_valid == get_pointer_type(ptrs[i]), "Funkcja heap_calloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptrs[i]));

                     for (size_t j = 0; j < mem_sizes[i] * mem_units[i]; ++j)
                         test_error(ptrs[i][j] == 0, "Funkcja heap_calloc() powinna zwrócić wskaźnik na obszar pamięci wypełniony wartościami 0");

                     status = heap_validate();
                     test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                 }

                 heap_free(ptrs[5]);

                 test_error(pointer_unallocated == get_pointer_type(ptrs[5]), "Funkcja heap_calloc() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptrs[5]));

                 status = heap_validate();
                 test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 void *ptr = heap_calloc(762, 3);
                 test_error(ptrs[5] == ptr, "Funkcja heap_calloc() powinna zwrócić adres równy adresowi ptrs[5] (jest możliwość wykorzystania wolnego bloku pamięci do zaalokowania), a zwróciła różny");

                 for (size_t j = 0; j < 762 * 3; ++j)
                     test_error(ptrs[5][j] == 0, "Funkcja heap_calloc() powinna zwrócić wskaźnik na obszar pamięci wypełniony wartościami 0");


                 status = heap_validate();
                 test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
             
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 27: Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń poprzednio zwolnionej
//
void UTEST27(void)
{
    // informacje o teście
    test_start(27, "Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń poprzednio zwolnionej", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr1 = heap_calloc(98, 1);
                char *ptr2 = heap_calloc(150, 1);
                char *ptr3 = heap_calloc(296, 1);

                test_error(ptr1 != NULL, "Funkcja heap_calloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(ptr2 != NULL, "Funkcja heap_calloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(ptr3 != NULL, "Funkcja heap_calloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");

                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));
                test_error(pointer_valid == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr2));
                test_error(pointer_valid == get_pointer_type(ptr3), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr3));

                for (int i = 0; i < 98; ++i)
                    test_error(ptr1[i] == 0, "Funkcja heap_calloc() powinna zwrócić wskaźnik na obszar pamięci wypełniony wartościami 0");

                for (int i = 0; i < 150; ++i)
                    test_error(ptr2[i] == 0, "Funkcja heap_calloc() powinna zwrócić wskaźnik na obszar pamięci wypełniony wartościami 0");
     
                for (int i = 0; i < 296; ++i)
                    test_error(ptr3[i] == 0, "Funkcja heap_calloc() powinna zwrócić wskaźnik na obszar pamięci wypełniony wartościami 0");

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                heap_free(ptr2);

                test_error(pointer_unallocated == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr2));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr4 = heap_calloc(158, 1);

                test_error(ptr2 != ptr4, "Funkcja heap_calloc() powinna zwrócić adres równy adresowi ptr2 (jest możliwość wykorzystania wolnego bloku pamięci do zaalokowania), a zwróciła różny");
                test_error(ptr4 != NULL, "Funkcja heap_calloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr4), "Funkcja heap_calloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr4));

                for (int i = 0; i < 158; ++i)
                    test_error(ptr4[i] == 0, "Funkcja heap_calloc() powinna zwrócić wskaźnik na obszar pamięci wypełniony wartościami 0");

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 28: Sprawdzanie poprawności działania funkcji heap_get_largest_used_block_size
//
void UTEST28(void)
{
    // informacje o teście
    test_start(28, "Sprawdzanie poprawności działania funkcji heap_get_largest_used_block_size", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    

                size_t block_size = heap_get_largest_used_block_size();
                test_error(block_size == 0, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 0, a zwróciła na %lu", block_size);

                heap_clean();
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 29: Sprawdzanie poprawności działania funkcji heap_get_largest_used_block_size
//
void UTEST29(void)
{
    // informacje o teście
    test_start(29, "Sprawdzanie poprawności działania funkcji heap_get_largest_used_block_size", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                size_t block_size = heap_get_largest_used_block_size();
                test_error(block_size == 0, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 0, a zwróciła na %lu", block_size);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 30: Sprawdzanie poprawności działania funkcji heap_get_largest_used_block_size
//
void UTEST30(void)
{
    // informacje o teście
    test_start(30, "Sprawdzanie poprawności działania funkcji heap_get_largest_used_block_size", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                size_t mem_sizes[] = {564, 301, 959, 386, 949, 990, 948, 309, 783, 645, 677, 950, 582, 748, 336, 699, 594, 241, 945, 317, 869, 834, 327, 297, 641, 149, 750, 507};
                void *ptrs[28];

                for (int i = 0; i < 28; ++i)
                {
                    ptrs[i] = heap_malloc(mem_sizes[i]);
                    test_error(pointer_valid == get_pointer_type(ptrs[i]), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptrs[i]));

                    status = heap_validate();
                    test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                }           


                size_t block_size = heap_get_largest_used_block_size();
                test_error(block_size == 990, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 990, a zwróciła na %lu", block_size);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 31: Sprawdzanie poprawności działania funkcji heap_get_largest_used_block_size
//
void UTEST31(void)
{
    // informacje o teście
    test_start(31, "Sprawdzanie poprawności działania funkcji heap_get_largest_used_block_size", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                 int status = heap_setup();
                 test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 size_t mem_sizes[] = {765, 319, 947, 448, 464, 639, 536, 648, 287, 305, 495, 396, 480, 489, 250, 362, 149, 233, 981, 549, 613, 916, 507, 145, 496, 819, 281, 788};
                 size_t mem_units[] = {1, 5, 3, 3, 2, 2, 2, 1, 4, 2, 2, 1, 1, 3, 1, 5, 4, 3, 3, 5, 2, 2, 3, 4, 3, 2, 4, 2};
                 char *ptrs[28];

                 for (int i = 0; i < 28; ++i)
                 {
                     ptrs[i] = heap_calloc(mem_sizes[i], mem_units[i]);
                     test_error(ptrs[i] != NULL, "Funkcja heap_calloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");

                     status = heap_validate();
                     test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                 }

                 size_t block_size = heap_get_largest_used_block_size();
                 test_error(block_size == 2943, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 2943, a zwróciła na %lu", block_size);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
             
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 32: Sprawdzanie poprawności działania funkcji heap_get_largest_used_block_size
//
void UTEST32(void)
{
    // informacje o teście
    test_start(32, "Sprawdzanie poprawności działania funkcji heap_get_largest_used_block_size", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                size_t mem_sizes[] = {923, 345, 200, 493, 205, 197, 418, 312, 538, 700, 497, 970, 125, 566, 290, 958, 659, 782, 752, 126, 875, 619, 630, 937, 261, 101, 420, 609, 829, 940, 543, 563, 937, 548, 732, 884, 329};
                char *ptrs[37];

                for (int i = 0; i < 37; ++i)
                {
                    ptrs[i] = heap_malloc(mem_sizes[i]);
                    test_error(pointer_valid == get_pointer_type(ptrs[i]), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptrs[i]));

                    status = heap_validate();
                    test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                }           

                ptrs[35][-1] += 10 ;

                status = heap_validate();
                test_error(status == 1, "Funkcja heap_validate() powinna zwrócić wartość 1, a zwróciła na %d", status);

                size_t block_size = heap_get_largest_used_block_size();
                test_error(block_size == 0, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 0, a zwróciła na %lu", block_size);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 33: Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku przekazania do niej niepoprawnego wskaźnika lub wskaźnika sprzed inicjalizacji sterty
//
void UTEST33(void)
{
    // informacje o teście
    test_start(33, "Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku przekazania do niej niepoprawnego wskaźnika lub wskaźnika sprzed inicjalizacji sterty", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                char *ptr = (char *)(intptr_t)rand();
                
                heap_free(ptr);
                
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);
            
                heap_free(NULL);
                
                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                heap_free(ptr);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                

            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 34: Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku przekazania do niej niepoprawnego wskaźnika
//
void UTEST34(void)
{
    // informacje o teście
    test_start(34, "Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku przekazania do niej niepoprawnego wskaźnika", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr = heap_malloc(61);
                test_error(ptr != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                heap_free(ptr + 1);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 61, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 61, a zwróciła na %llu", heap_get_largest_used_block_size());

                heap_free(ptr - 1);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 61, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 61, a zwróciła na %llu", heap_get_largest_used_block_size());

                heap_free(ptr + 62);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 61, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 61, a zwróciła na %llu", heap_get_largest_used_block_size());

                heap_free(ptr - 20);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 61, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 61, a zwróciła na %llu", heap_get_largest_used_block_size());

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 35: Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku przekazania do niej niepoprawnego wskaźnika
//
void UTEST35(void)
{
    // informacje o teście
    test_start(35, "Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku przekazania do niej niepoprawnego wskaźnika", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr1 = heap_malloc(302);
                test_error(ptr1 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));

                void *ptr2 = heap_malloc(50);
                test_error(ptr2 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr2));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 302, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 302, a zwróciła na %llu", heap_get_largest_used_block_size());

                heap_free(ptr1);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 50, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 50, a zwróciła na %llu", heap_get_largest_used_block_size());

                test_error(pointer_unallocated == get_pointer_type(ptr1), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr1));

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 36: Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku przekazania do niej niepoprawnego wskaźnika
//
void UTEST36(void)
{
    // informacje o teście
    test_start(36, "Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku przekazania do niej niepoprawnego wskaźnika", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr1 = heap_malloc(345);
                test_error(ptr1 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 345, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 345, a zwróciła na %llu", heap_get_largest_used_block_size());

                heap_free(ptr1);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %llu", heap_get_largest_used_block_size());

                test_error(pointer_unallocated == get_pointer_type(ptr1), "Funkcja get_pointer_type() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr1));

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 37: Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku przekazania do niej niepoprawnego wskaźnika
//
void UTEST37(void)
{
    // informacje o teście
    test_start(37, "Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku przekazania do niej niepoprawnego wskaźnika", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr1 = heap_malloc(331);
                test_error(ptr1 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));

                void *ptr2 = heap_malloc(99);
                test_error(ptr2 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr2));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 331, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 331, a zwróciła na %llu", heap_get_largest_used_block_size());

                heap_free(ptr1);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 99, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 99, a zwróciła na %llu", heap_get_largest_used_block_size());

                test_error(pointer_unallocated == get_pointer_type(ptr1), "Funkcja get_pointer_type() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr1));

                heap_free(ptr2);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %llu", heap_get_largest_used_block_size());

                test_error(pointer_unallocated == get_pointer_type(ptr2), "Funkcja get_pointer_type() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr2));


                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 38: Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia dwóch bloków pamięci sąsiadujących ze sobą
//
void UTEST38(void)
{
    // informacje o teście
    test_start(38, "Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia dwóch bloków pamięci sąsiadujących ze sobą", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr1 = heap_malloc(341);
                test_error(ptr1 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));

                void *ptr2 = heap_malloc(546);
                test_error(ptr2 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr2));

                void *ptr3 = heap_malloc(73);
                test_error(ptr3 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr3), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr3));


                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 546, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 546, a zwróciła na %llu", heap_get_largest_used_block_size());

                heap_free(ptr2);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 341, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 341, a zwróciła na %llu", heap_get_largest_used_block_size());

                test_error(pointer_unallocated == get_pointer_type(ptr2), "Funkcja get_pointer_type() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr2));

                heap_free(ptr1);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 73, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 73, a zwróciła na %llu", heap_get_largest_used_block_size());

                test_error(pointer_unallocated == get_pointer_type(ptr1), "Funkcja get_pointer_type() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr1));

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 39: Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia dwóch bloków pamięci sąsiadujących ze sobą i zaalokowanie w tym miejscu nowej pamięci o rozmiarze sumy dwóch zwolnionych bloków
//
void UTEST39(void)
{
    // informacje o teście
    test_start(39, "Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia dwóch bloków pamięci sąsiadujących ze sobą i zaalokowanie w tym miejscu nowej pamięci o rozmiarze sumy dwóch zwolnionych bloków", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr1 = heap_malloc(369);
                test_error(ptr1 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));

                void *ptr2 = heap_malloc(989);
                test_error(ptr2 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr2));

                void *ptr3 = heap_malloc(68);
                test_error(ptr3 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr3), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr3));


                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 989, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 989, a zwróciła na %llu", heap_get_largest_used_block_size());

                heap_free(ptr2);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 369, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 369, a zwróciła na %llu", heap_get_largest_used_block_size());

                test_error(pointer_unallocated == get_pointer_type(ptr2), "Funkcja get_pointer_type() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr2));

                heap_free(ptr1);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 68, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 68, a zwróciła na %llu", heap_get_largest_used_block_size());

                test_error(pointer_unallocated == get_pointer_type(ptr1), "Funkcja get_pointer_type() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr1));

                void *ptr4 = heap_malloc(1368);
                test_error(ptr4 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr4), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr4));
                test_error(ptr1 == ptr4, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego pierwszego bloku pamięci");
                test_error(heap_get_largest_used_block_size() == 1368, "Funkcja heap_validate() powinna zwrócić wartość 1368, a zwróciła na %llu", heap_get_largest_used_block_size());

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 40: Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia dwóch bloków pamięci sąsiadujących ze sobą
//
void UTEST40(void)
{
    // informacje o teście
    test_start(40, "Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia dwóch bloków pamięci sąsiadujących ze sobą", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr1 = heap_malloc(262);
                test_error(ptr1 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));

                void *ptr2 = heap_malloc(6780);
                test_error(ptr2 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr2));

                void *ptr3 = heap_malloc(902);
                test_error(ptr3 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr3), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr3));

                void *ptr4 = heap_malloc(64);
                test_error(ptr4 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr4), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr4));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 6780, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 6780, a zwróciła na %llu", heap_get_largest_used_block_size());

                heap_free(ptr2);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 902, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 902, a zwróciła na %llu", heap_get_largest_used_block_size());

                test_error(pointer_unallocated == get_pointer_type(ptr2), "Funkcja get_pointer_type() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr2));

                heap_free(ptr3);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 262, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 262, a zwróciła na %llu", heap_get_largest_used_block_size());

                test_error(pointer_unallocated == get_pointer_type(ptr3), "Funkcja get_pointer_type() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr3));

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 41: Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia dwóch bloków pamięci sąsiadujących ze sobą i zaalokowanie w tym miejscu nowej pamięci o rozmiarze sumy dwóch zwolnionych bloków
//
void UTEST41(void)
{
    // informacje o teście
    test_start(41, "Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia dwóch bloków pamięci sąsiadujących ze sobą i zaalokowanie w tym miejscu nowej pamięci o rozmiarze sumy dwóch zwolnionych bloków", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr1 = heap_malloc(372);
                test_error(ptr1 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));

                void *ptr2 = heap_malloc(6384);
                test_error(ptr2 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr2));

                void *ptr3 = heap_malloc(701);
                test_error(ptr3 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr3), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr3));

                void *ptr4 = heap_malloc(83);
                test_error(ptr4 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr4), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr4));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 6384, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 6384, a zwróciła na %llu", heap_get_largest_used_block_size());

                heap_free(ptr2);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 701, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 701, a zwróciła na %llu", heap_get_largest_used_block_size());

                test_error(pointer_unallocated == get_pointer_type(ptr2), "Funkcja get_pointer_type() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr2));

                heap_free(ptr3);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 372, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 372, a zwróciła na %llu", heap_get_largest_used_block_size());

                test_error(pointer_unallocated == get_pointer_type(ptr3), "Funkcja get_pointer_type() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr3));

                void *ptr = heap_malloc(7098);
                test_error(ptr != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr));
                test_error(ptr2 == ptr, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego pierwszego bloku pamięci");
                test_error(heap_get_largest_used_block_size() == 7098, "Funkcja heap_validate() powinna zwrócić wartość 7098, a zwróciła na %llu", heap_get_largest_used_block_size());


                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 42: Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia trzech bloków pamięci sąsiadujących ze sobą
//
void UTEST42(void)
{
    // informacje o teście
    test_start(42, "Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia trzech bloków pamięci sąsiadujących ze sobą", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr1 = heap_malloc(9195);
                test_error(ptr1 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));

                void *ptr2 = heap_malloc(282);
                test_error(ptr2 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr2));

                void *ptr3 = heap_malloc(923);
                test_error(ptr3 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr3), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr3));

                void *ptr4 = heap_malloc(93);
                test_error(ptr4 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr4), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr4));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 9195, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 9195, a zwróciła na %llu", heap_get_largest_used_block_size());

                heap_free(ptr1);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 923, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 923, a zwróciła na %llu", heap_get_largest_used_block_size());

                test_error(pointer_unallocated == get_pointer_type(ptr1), "Funkcja get_pointer_type() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr1));

                heap_free(ptr3);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 282, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 282, a zwróciła na %llu", heap_get_largest_used_block_size());
                test_error(pointer_unallocated == get_pointer_type(ptr3), "Funkcja get_pointer_type() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr3));

                heap_free(ptr2);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 93, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 93, a zwróciła na %llu", heap_get_largest_used_block_size());
                test_error(pointer_unallocated == get_pointer_type(ptr3), "Funkcja get_pointer_type() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr3));


                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 43: Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia trzech bloków pamięci sąsiadujących ze sobą i zaalokowanie w tym miejscu nowej pamięci o rozmiarze sumy dwóch zwolnionych bloków
//
void UTEST43(void)
{
    // informacje o teście
    test_start(43, "Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia trzech bloków pamięci sąsiadujących ze sobą i zaalokowanie w tym miejscu nowej pamięci o rozmiarze sumy dwóch zwolnionych bloków", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr1 = heap_malloc(8298);
                test_error(ptr1 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));

                void *ptr2 = heap_malloc(284);
                test_error(ptr2 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr2));

                void *ptr3 = heap_malloc(839);
                test_error(ptr3 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr3), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr3));

                void *ptr4 = heap_malloc(100);
                test_error(ptr4 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr4), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr4));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 8298, "Funkcja heap_validate() powinna zwrócić wartość 8298, a zwróciła na %llu", heap_get_largest_used_block_size());

                heap_free(ptr1);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 839, "Funkcja heap_validate() powinna zwrócić wartość 839, a zwróciła na %llu", heap_get_largest_used_block_size());

                test_error(pointer_unallocated == get_pointer_type(ptr1), "Funkcja get_pointer_type() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr1));

                heap_free(ptr3);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 284, "Funkcja heap_validate() powinna zwrócić wartość 284, a zwróciła na %llu", heap_get_largest_used_block_size());
                test_error(pointer_unallocated == get_pointer_type(ptr3), "Funkcja get_pointer_type() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr3));

                heap_free(ptr2);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 100, "Funkcja heap_validate() powinna zwrócić wartość 100, a zwróciła na %llu", heap_get_largest_used_block_size());
                test_error(pointer_unallocated == get_pointer_type(ptr3), "Funkcja get_pointer_type() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr3));

                void *ptr = heap_malloc(9433);
                test_error(ptr != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr));
                test_error(ptr1 == ptr, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego pierwszego bloku pamięci");
                test_error(heap_get_largest_used_block_size() == 9433, "Funkcja heap_validate() powinna zwrócić wartość 9433, a zwróciła na %llu", heap_get_largest_used_block_size());

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 44: Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia bloku pamięci, zaalokowania w to miejsce mniejszego bloku, zwolnienia go i zaalokowania ponownie większego bloku
//
void UTEST44(void)
{
    // informacje o teście
    test_start(44, "Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia bloku pamięci, zaalokowania w to miejsce mniejszego bloku, zwolnienia go i zaalokowania ponownie większego bloku", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr1 = heap_malloc(387);
                test_error(ptr1 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));

                void *ptr2 = heap_malloc(55);
                test_error(ptr2 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr2));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 387, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 387, a zwróciła na %llu", heap_get_largest_used_block_size());

                heap_free(ptr1);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 55, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 55, a zwróciła na %llu", heap_get_largest_used_block_size());

                test_error(pointer_unallocated == get_pointer_type(ptr1), "Funkcja get_pointer_type() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr1));

                void *ptr3 = heap_malloc(364);
                test_error(ptr3 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(ptr3 == ptr1, "Funkcja heap_malloc() powinna zwrócić adres pierwszego wolnego bloku pamięci");
                test_error(pointer_valid == get_pointer_type(ptr3), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr3));

                test_error(heap_get_largest_used_block_size() == 364, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 364, a zwróciła na %llu", heap_get_largest_used_block_size());

                heap_free(ptr3);

                void *ptr4 = heap_malloc(387);
                test_error(ptr4 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(ptr4 == ptr1, "Funkcja heap_malloc() powinna zwrócić adres pierwszego wolnego bloku pamięci");
                test_error(pointer_valid == get_pointer_type(ptr4), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr4));

                test_error(heap_get_largest_used_block_size() == 387, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 387, a zwróciła na %llu", heap_get_largest_used_block_size());


                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 45: Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia trzech bloków pamięci sąsiadujących ze sobą i zaalokowanie w tym miejscu nowej pamięci o rozmiarze sumy dwóch zwolnionych bloków
//
void UTEST45(void)
{
    // informacje o teście
    test_start(45, "Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia trzech bloków pamięci sąsiadujących ze sobą i zaalokowanie w tym miejscu nowej pamięci o rozmiarze sumy dwóch zwolnionych bloków", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr1 = heap_malloc(838);
                test_error(ptr1 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));

                void *ptr2 = heap_malloc(312);
                test_error(ptr2 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr2));

                void *ptr3 = heap_malloc(9823);
                test_error(ptr3 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr3), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr3));

                void *ptr4 = heap_malloc(98);
                test_error(ptr4 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr4), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr4));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 9823, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 9823, a zwróciła na %llu", heap_get_largest_used_block_size());

                heap_free(ptr3);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 838, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 838, a zwróciła na %llu", heap_get_largest_used_block_size());

                test_error(pointer_unallocated == get_pointer_type(ptr3), "Funkcja get_pointer_type() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr3));

                void *ptr5 = heap_malloc(6736);
                test_error(ptr5 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(ptr5 == ptr3, "Funkcja heap_malloc() powinna zwrócić adres pierwszego wolnego bloku pamięci");
                test_error(pointer_valid == get_pointer_type(ptr5), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr5));

                test_error(heap_get_largest_used_block_size() == 6736, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 6736, a zwróciła na %llu", heap_get_largest_used_block_size());

                heap_free(ptr5);
                heap_free(ptr2);
                
                void *ptr6 = heap_malloc(1159);
                test_error(ptr6 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(ptr6 == ptr2, "Funkcja heap_malloc() powinna zwrócić adres pierwszego wolnego bloku pamięci");
                test_error(pointer_valid == get_pointer_type(ptr6), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr6));

                test_error(heap_get_largest_used_block_size() == 1159, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 1159, a zwróciła na %llu", heap_get_largest_used_block_size());

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                

            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 46: Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia trzech bloków pamięci sąsiadujących ze sobą i zaalokowanie w tym miejscu nowej pamięci o rozmiarze sumy dwóch zwolnionych bloków
//
void UTEST46(void)
{
    // informacje o teście
    test_start(46, "Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia trzech bloków pamięci sąsiadujących ze sobą i zaalokowanie w tym miejscu nowej pamięci o rozmiarze sumy dwóch zwolnionych bloków", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr1 = heap_malloc(628);
                test_error(ptr1 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));

                void *ptr2 = heap_malloc(333);
                test_error(ptr2 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr2));

                void *ptr3 = heap_malloc(9271);
                test_error(ptr3 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr3), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr3));

                void *ptr4 = heap_malloc(84);
                test_error(ptr4 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr4), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr4));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 9271, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 9271, a zwróciła na %llu", heap_get_largest_used_block_size());

                heap_free(ptr3);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 628, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 628, a zwróciła na %llu", heap_get_largest_used_block_size());

                test_error(pointer_unallocated == get_pointer_type(ptr3), "Funkcja get_pointer_type() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr3));

                void *ptr5 = heap_malloc(6325);
                test_error(ptr5 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(ptr5 == ptr3, "Funkcja heap_malloc() powinna zwrócić adres pierwszego wolnego bloku pamięci");
                test_error(pointer_valid == get_pointer_type(ptr5), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr5));

                test_error(heap_get_largest_used_block_size() == 6325, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 6325, a zwróciła na %llu", heap_get_largest_used_block_size());

                heap_free(ptr2);
                heap_free(ptr5);

                void *ptr6 = heap_malloc(969);
                test_error(ptr6 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(ptr6 == ptr2, "Funkcja heap_malloc() powinna zwrócić adres pierwszego wolnego bloku pamięci");
                test_error(pointer_valid == get_pointer_type(ptr6), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr6));

                test_error(heap_get_largest_used_block_size() == 969, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 969, a zwróciła na %llu", heap_get_largest_used_block_size());

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 47: Sprawdzanie poprawności działania funkcji heap_malloc, heap_calloc i heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia trzech bloków pamięci sąsiadujących ze sobą i zaalokowanie w tym miejscu nowej pamięci o rozmiarze sumy dwóch zwolnionych bloków
//
void UTEST47(void)
{
    // informacje o teście
    test_start(47, "Sprawdzanie poprawności działania funkcji heap_malloc, heap_calloc i heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia trzech bloków pamięci sąsiadujących ze sobą i zaalokowanie w tym miejscu nowej pamięci o rozmiarze sumy dwóch zwolnionych bloków", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr1 = heap_malloc(6382);
                test_error(ptr1 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr1), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr1));

                void *ptr2 = heap_malloc(354);
                test_error(ptr2 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr2), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr2));

                void *ptr3 = heap_calloc(742, 1);
                test_error(ptr3 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr3), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr3));

                void *ptr4 = heap_malloc(53);
                test_error(ptr4 != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr4), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr4));

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 6382, "Funkcja heap_validate() powinna zwrócić wartość 6382, a zwróciła na %llu", heap_get_largest_used_block_size());

                heap_free(ptr1);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 742, "Funkcja heap_validate() powinna zwrócić wartość 742, a zwróciła na %llu", heap_get_largest_used_block_size());

                test_error(pointer_unallocated == get_pointer_type(ptr1), "Funkcja get_pointer_type() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr1));

                heap_free(ptr3);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 354, "Funkcja heap_validate() powinna zwrócić wartość 354, a zwróciła na %llu", heap_get_largest_used_block_size());
                test_error(pointer_unallocated == get_pointer_type(ptr3), "Funkcja get_pointer_type() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr3));

                heap_free(ptr2);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
                test_error(heap_get_largest_used_block_size() == 53, "Funkcja heap_validate() powinna zwrócić wartość 53, a zwróciła na %llu", heap_get_largest_used_block_size());
                test_error(pointer_unallocated == get_pointer_type(ptr3), "Funkcja get_pointer_type() powinna zwrócić wskaźnik typu pointer_unallocated, a zwróciła %d", get_pointer_type(ptr3));

                void *ptr = heap_malloc(7489);
                test_error(ptr != NULL, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego bloku pamięci, a zwróciła NULL");
                test_error(pointer_valid == get_pointer_type(ptr), "Funkcja heap_malloc() powinna zwrócić wskaźnik typu pointer_valid, a zwróciła %d", get_pointer_type(ptr));
                test_error(ptr1 == ptr, "Funkcja heap_malloc() powinna zwrócić adres przydzielonego pierwszego bloku pamięci");
                test_error(heap_get_largest_used_block_size() == 7489, "Funkcja heap_validate() powinna zwrócić wartość 7489, a zwróciła na %llu", heap_get_largest_used_block_size());

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 48: Sprawdzanie poprawności działania funkcji heap_malloc i heap_free
//
void UTEST48(void)
{
    // informacje o teście
    test_start(48, "Sprawdzanie poprawności działania funkcji heap_malloc i heap_free", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                  srand (time(NULL));

                  int status = heap_setup();
                  test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                  char *ptr[2150];
                  int ptr_state[2150] = {0};

                  int is_allocated = 0;

                  for (int i = 0; i < 2150; ++i)
                  {
                    if (rand() % 100 < 66)
                    {
                      for (int j = 0; j < 2150; ++j)
                        if (ptr_state[j] == 0)
                        {
                          ptr_state[j] = 1;
                          ptr[j] = heap_malloc(rand() % 100 + 50);
                          is_allocated++;
                          break;
                        }
                    }
                    else
                    {
                      if (is_allocated)
                      {
                        int to_free = rand() % is_allocated;
                         for (int j = 0; j < 2150; ++j)
                          {
                              if (ptr_state[j] == 1 && !to_free)
                              {
                                ptr_state[j] = 0;
                                is_allocated--;
                                heap_free(ptr[j]);
                                break;
                              }        
                              to_free--;
                          }
                      }
                    }
                  }

                  for (int j = 0; j < 2150; ++j)
                    if (ptr_state[j] == 1)
                      heap_free(ptr[j]);

                  test_error(heap_get_largest_used_block_size() == 0, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 0, a zwróciła na %llu", heap_get_largest_used_block_size());

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 49: Sprawdzanie poprawności działania funkcji get_pointer_type
//
void UTEST49(void)
{
    // informacje o teście
    test_start(49, "Sprawdzanie poprawności działania funkcji get_pointer_type", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                test_error(get_pointer_type(NULL) == pointer_null, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_null, a zwróciła %d", get_pointer_type(NULL));

            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 50: Sprawdzanie poprawności działania funkcji get_pointer_type
//
void UTEST50(void)
{
    // informacje o teście
    test_start(50, "Sprawdzanie poprawności działania funkcji get_pointer_type", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                test_error(get_pointer_type(NULL) == pointer_null, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_null, a zwróciła %d", get_pointer_type(NULL));

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 51: Sprawdzanie poprawności działania funkcji get_pointer_type
//
void UTEST51(void)
{
    // informacje o teście
    test_start(51, "Sprawdzanie poprawności działania funkcji get_pointer_type", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr = heap_malloc(175);

                test_error(get_pointer_type(ptr) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr));

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 52: Sprawdzanie poprawności działania funkcji get_pointer_type
//
void UTEST52(void)
{
    // informacje o teście
    test_start(52, "Sprawdzanie poprawności działania funkcji get_pointer_type", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr = heap_malloc(151);
                char *ptr1 = heap_malloc(936);

                test_error(get_pointer_type(ptr) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr));
                test_error(get_pointer_type(ptr1) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr1));

                heap_free(ptr);

                test_error(get_pointer_type(ptr) == pointer_unallocated, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_unallocated, a zwróciła %d", get_pointer_type(ptr));
                test_error(get_pointer_type(ptr + 32) == pointer_unallocated, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_unallocated, a zwróciła %d", get_pointer_type(ptr + 32));
                test_error(get_pointer_type(ptr + 151) == pointer_unallocated, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_unallocated, a zwróciła %d", get_pointer_type(ptr + 151));
                test_error(get_pointer_type(ptr - 1) == pointer_unallocated, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_unallocated, a zwróciła %d", get_pointer_type(ptr - 1));

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 53: Sprawdzanie poprawności działania funkcji get_pointer_type
//
void UTEST53(void)
{
    // informacje o teście
    test_start(53, "Sprawdzanie poprawności działania funkcji get_pointer_type", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr = heap_malloc(1568);
                char *ptr1 = heap_malloc(1096);

                test_error(get_pointer_type(ptr) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr));
                test_error(get_pointer_type(ptr1) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr1));

                test_error(get_pointer_type(ptr + 1568) == pointer_inside_fences, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_inside_fences, a zwróciła %d", get_pointer_type(ptr + 1568));
                test_error(get_pointer_type(ptr - 1) == pointer_inside_fences, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_inside_fences, a zwróciła %d", get_pointer_type(ptr - 1));

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 54: Sprawdzanie poprawności działania funkcji get_pointer_type
//
void UTEST54(void)
{
    // informacje o teście
    test_start(54, "Sprawdzanie poprawności działania funkcji get_pointer_type", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr = heap_malloc(896);

                test_error(get_pointer_type(ptr) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr));

                for (int i = 1; i < 896; ++i)
                    test_error(get_pointer_type(ptr + i) == pointer_inside_data_block, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_inside_data_block, a zwróciła %d", get_pointer_type(ptr + i));

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 55: Sprawdzanie poprawności działania funkcji get_pointer_type
//
void UTEST55(void)
{
    // informacje o teście
    test_start(55, "Sprawdzanie poprawności działania funkcji get_pointer_type", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr = heap_malloc(1184);
                char *ptr1 = heap_malloc(1240);

                test_error(get_pointer_type(ptr1) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr1));

                int i = -1;

                while (get_pointer_type(ptr1 + i) == pointer_inside_fences) --i;

                test_error(get_pointer_type(ptr1 + i) == pointer_control_block, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_control_block, a zwróciła %d", get_pointer_type(ptr + i));

                while (get_pointer_type(ptr1 + i) == pointer_control_block) --i;

                test_error(get_pointer_type(ptr1 + i) == pointer_inside_fences, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_inside_fences, a zwróciła %d", get_pointer_type(ptr + i));

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 56: Sprawdzanie poprawności działania funkcji get_pointer_type
//
void UTEST56(void)
{
    // informacje o teście
    test_start(56, "Sprawdzanie poprawności działania funkcji get_pointer_type", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr = heap_malloc(1448);
                char *ptr1 = heap_malloc(896);

                test_error(get_pointer_type(ptr1) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr1));

                int i = 1448 + 1;

                while (get_pointer_type(ptr + i) == pointer_inside_fences) ++i;

                test_error(get_pointer_type(ptr + i) == pointer_control_block, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_control_block, a zwróciła %d", get_pointer_type(ptr + i));

                while (get_pointer_type(ptr + i) == pointer_control_block) ++i;

                test_error(get_pointer_type(ptr + i) == pointer_inside_fences, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_inside_fences, a zwróciła %d", get_pointer_type(ptr + i));

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 57: Sprawdzanie poprawności działania funkcji get_pointer_type
//
void UTEST57(void)
{
    // informacje o teście
    test_start(57, "Sprawdzanie poprawności działania funkcji get_pointer_type", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr = heap_malloc(1176);
                char *ptr1 = heap_malloc(896);

                test_error(get_pointer_type(ptr) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr));
                test_error(get_pointer_type(ptr1) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr1));

                int i = -1, fences_size_before = 0, fences_size_after = 0;

                while (get_pointer_type(ptr + i) == pointer_inside_fences) 
                {
                    fences_size_before++;
                    --i;
                }

                i = 1176 + 1;

                while (get_pointer_type(ptr + i) == pointer_inside_fences)             
                {
                    fences_size_after++;
                    ++i;
                }

                heap_free(ptr);

                for (int i = -fences_size_before; i < 1176 + fences_size_after; ++i)
                    test_error(get_pointer_type(ptr + i) == pointer_unallocated, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_unallocated, a zwróciła %d", get_pointer_type(ptr + i));

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                

            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 58: Sprawdzanie poprawności działania funkcji get_pointer_type
//
void UTEST58(void)
{
    // informacje o teście
    test_start(58, "Sprawdzanie poprawności działania funkcji get_pointer_type", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr = heap_calloc(177, 116);

                test_error(get_pointer_type(ptr) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr));

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
        
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 59: Sprawdzanie poprawności działania funkcji get_pointer_type
//
void UTEST59(void)
{
    // informacje o teście
    test_start(59, "Sprawdzanie poprawności działania funkcji get_pointer_type", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr = heap_calloc(984, 19);
                char *ptr1 = heap_calloc(1064, 19);

                test_error(get_pointer_type(ptr) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr));
                test_error(get_pointer_type(ptr1) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr1));

                heap_free(ptr);

                test_error(get_pointer_type(ptr) == pointer_unallocated, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_unallocated, a zwróciła %d", get_pointer_type(ptr));
                test_error(get_pointer_type(ptr + 36) == pointer_unallocated, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_unallocated, a zwróciła %d", get_pointer_type(ptr + 36));
                test_error(get_pointer_type(ptr + 18696) == pointer_unallocated, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_unallocated, a zwróciła %d", get_pointer_type(ptr + 984));
                test_error(get_pointer_type(ptr - 1) == pointer_unallocated, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_unallocated, a zwróciła %d", get_pointer_type(ptr - 1));

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
                
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 60: Sprawdzanie poprawności działania funkcji get_pointer_type
//
void UTEST60(void)
{
    // informacje o teście
    test_start(60, "Sprawdzanie poprawności działania funkcji get_pointer_type", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr = heap_calloc(1568, 19);
                char *ptr1 = heap_calloc(1024, 19);


                test_error(get_pointer_type(ptr) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr));
                test_error(get_pointer_type(ptr1) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr1));

                test_error(get_pointer_type(ptr + 29792) == pointer_inside_fences, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_inside_fences, a zwróciła %d", get_pointer_type(ptr + 1568));
                test_error(get_pointer_type(ptr - 1) == pointer_inside_fences, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_inside_fences, a zwróciła %d", get_pointer_type(ptr - 1));

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);

            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 61: Sprawdzanie poprawności działania funkcji get_pointer_type
//
void UTEST61(void)
{
    // informacje o teście
    test_start(61, "Sprawdzanie poprawności działania funkcji get_pointer_type", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr = heap_calloc(1112, 13);

                test_error(get_pointer_type(ptr) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr));

                for (int i = 1; i < 14456; ++i)
                    test_error(get_pointer_type(ptr + i) == pointer_inside_data_block, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_inside_data_block, a zwróciła %d", get_pointer_type(ptr + i));

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 62: Sprawdzanie poprawności działania funkcji get_pointer_type
//
void UTEST62(void)
{
    // informacje o teście
    test_start(62, "Sprawdzanie poprawności działania funkcji get_pointer_type", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr = heap_calloc(1448, 18);
                char *ptr1 = heap_calloc(1280, 18);

                test_error(get_pointer_type(ptr1) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr1));

                int i = -1;

                while (get_pointer_type(ptr1 + i) == pointer_inside_fences) --i;

                test_error(get_pointer_type(ptr1 + i) == pointer_control_block, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_control_block, a zwróciła %d", get_pointer_type(ptr + i));

                while (get_pointer_type(ptr1 + i) == pointer_control_block) --i;

                test_error(get_pointer_type(ptr1 + i) == pointer_inside_fences, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_inside_fences, a zwróciła %d", get_pointer_type(ptr + i));

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 63: Sprawdzanie poprawności działania funkcji heap_validate
//
void UTEST63(void)
{
    // informacje o teście
    test_start(63, "Sprawdzanie poprawności działania funkcji heap_validate", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_validate();
                test_error(status == 2, "Funkcja heap_validate() powinna zwrócić wartość 2, a zwróciła na %d", status);
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 64: Sprawdzanie poprawności działania funkcji heap_validate
//
void UTEST64(void)
{
    // informacje o teście
    test_start(64, "Sprawdzanie poprawności działania funkcji heap_validate", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr = heap_malloc(191);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                heap_free(ptr);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);
     
                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 65: Sprawdzanie poprawności działania funkcji heap_validate
//
void UTEST65(void)
{
    // informacje o teście
    test_start(65, "Sprawdzanie poprawności działania funkcji heap_validate", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr = heap_malloc(127);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                int i = -1;

                while (get_pointer_type(ptr + i) == pointer_inside_fences)
                {
                    char temp = ptr[i];
                    ptr[i] += 19;

                    status = heap_validate();
                    test_error(status == 1, "Funkcja heap_validate() powinna zwrócić wartość 1, a zwróciła na %d", status);

                    ptr[i] = temp;

                    status = heap_validate();
                    test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                    --i;
                }

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 66: Sprawdzanie poprawności działania funkcji heap_validate
//
void UTEST66(void)
{
    // informacje o teście
    test_start(66, "Sprawdzanie poprawności działania funkcji heap_validate", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr = heap_malloc(148);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                int i = 148;

                while (get_pointer_type(ptr + i) == pointer_inside_fences)
                {
                    char temp = ptr[i];
                    ptr[i] += 18;

                    status = heap_validate();
                    test_error(status == 1, "Funkcja heap_validate() powinna zwrócić wartość 1, a zwróciła na %d", status);

                    ptr[i] = temp;

                    status = heap_validate();
                    test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                    ++i;
                }

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 67: Sprawdzanie poprawności działania funkcji heap_validate
//
void UTEST67(void)
{
    // informacje o teście
    test_start(67, "Sprawdzanie poprawności działania funkcji heap_validate", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr = heap_malloc(103);
                char *ptr1 = heap_malloc(103);

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                test_error(get_pointer_type(ptr) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr));
                test_error(get_pointer_type(ptr1) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr1));

                int i = -1;

                while (get_pointer_type(ptr1 + i) == pointer_inside_fences) --i;

                while (get_pointer_type(ptr1 + i) == pointer_control_block)
                {
                    char temp = ptr1[i];
                    ptr1[i] += 14;

                    status = heap_validate();
                    test_error(status == 3, "Funkcja heap_validate() powinna zwrócić wartość 3, a zwróciła na %d", status);

                    ptr1[i] = temp;

                    status = heap_validate();
                    test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                    --i;
                }

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 68: Sprawdzanie poprawności działania funkcji heap_validate
//
void UTEST68(void)
{
    // informacje o teście
    test_start(68, "Sprawdzanie poprawności działania funkcji heap_validate", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                 int status = heap_setup();
                 test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 size_t mem_sizes[] = {400, 100, 362, 311, 130, 712, 737, 200, 578, 605, 683, 142, 605, 738, 672, 860, 198, 975, 936, 924, 659, 149, 585, 446, 267, 440, 890, 779, 564, 385, 858, 503, 299, 262, 749, 506, 518, 108, 467, 234};
                 size_t mem_units[] = {1, 4, 5, 4, 5, 3, 5, 2, 3, 2, 2, 1, 2, 2, 5, 1, 4, 1, 5, 5, 3, 4, 5, 4, 2, 4, 1, 5, 3, 4, 1, 1, 4, 1, 3, 4, 4, 5, 4, 4};
                 char *ptrs[40];

                 for (int i = 0; i < 40; ++i)
                     ptrs[i] = heap_calloc(mem_sizes[i], mem_units[i]);

                 ptrs[21][-1] += 7;
                 
                 status = heap_validate();
                 test_error(status == 1, "Funkcja heap_validate() powinna zwrócić wartość 1, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
             
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 69: Sprawdzanie poprawności działania funkcji heap_validate
//
void UTEST69(void)
{
    // informacje o teście
    test_start(69, "Sprawdzanie poprawności działania funkcji heap_validate", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                 int status = heap_setup();
                 test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 size_t mem_sizes[] = {377, 708, 780, 196, 489, 742, 941, 897, 406, 731, 937, 911, 298, 997, 670, 757, 754, 616, 116, 668, 248, 904, 853, 795, 409};
                 size_t mem_units[] = {1, 5, 5, 1, 5, 4, 4, 3, 3, 4, 4, 1, 1, 2, 4, 2, 2, 4, 3, 4, 4, 2, 1, 1, 2};
                 char *ptrs[25];

                 for (int i = 0; i < 25; ++i)
                     ptrs[i] = heap_calloc(mem_sizes[i], mem_units[i]);

                 ptrs[21][mem_sizes[21] * mem_units[21]] += 7;

                 status = heap_validate();
                 test_error(status == 1, "Funkcja heap_validate() powinna zwrócić wartość 1, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
             
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 70: Sprawdzanie poprawności działania funkcji heap_validate
//
void UTEST70(void)
{
    // informacje o teście
    test_start(70, "Sprawdzanie poprawności działania funkcji heap_validate", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    rldebug_heap_set_global_limit(0);
    
    //
    // -----------
    //
    
                 int status = heap_setup();
                 test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 size_t mem_sizes[] = {414, 506, 914, 707, 442, 592, 587, 853, 699, 855, 838, 980, 865, 812, 452, 122, 187, 900, 788, 447, 455, 800, 216, 647, 987, 602, 857, 179};
                 size_t mem_units[] = {3, 4, 1, 5, 5, 3, 2, 1, 1, 4, 3, 2, 5, 1, 5, 2, 5, 2, 1, 4, 1, 2, 3, 2, 3, 1, 2, 3};
                 char *ptrs[28];

                 for (int i = 0; i < 28; ++i)
                     ptrs[i] = heap_calloc(mem_sizes[i], mem_units[i]);

                 int i = -1;

                 while (get_pointer_type(ptrs[22] + i) == pointer_inside_fences) --i;

                 ptrs[22][i - 12] += 6;

                 status = heap_validate();
                 test_error(status == 3, "Funkcja heap_validate() powinna zwrócić wartość 3, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
             
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 71: Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej wartości 0
//
void UTEST71(void)
{
    // informacje o teście
    test_start(71, "Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej wartości 0", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr = heap_realloc(NULL, 0);

                test_error(ptr == NULL, "Funkcja heap_realloc() powinna zwrócić wartość NULL");

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 72: Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku niezainicjowania sterty
//
void UTEST72(void)
{
    // informacje o teście
    test_start(72, "Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku niezainicjowania sterty", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    

                void *ptr = heap_realloc(NULL, 156);

                test_error(ptr == NULL, "Funkcja heap_realloc() powinna zwrócić wartość NULL");
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 73: Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej poprawnej wartości
//
void UTEST73(void)
{
    // informacje o teście
    test_start(73, "Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej poprawnej wartości", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr = heap_realloc(NULL, 168);

                test_error(ptr != NULL, "Funkcja heap_realloc() powinna zwrócić adres pamięci przydzielonej użytkownikowi");
                test_error(get_pointer_type(ptr) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr));

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 74: Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej wartości 0
//
void UTEST74(void)
{
    // informacje o teście
    test_start(74, "Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej wartości 0", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                void *ptr = heap_realloc(NULL, 115);

                test_error(ptr != NULL, "Funkcja heap_realloc() powinna zwrócić adres pamięci przydzielonej użytkownikowi");
                test_error(get_pointer_type(ptr) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr));

                void *ptr1 = heap_realloc(ptr, 0);

                test_error(ptr1 == NULL, "Funkcja heap_realloc() powinna zwrócić wartość NULL");
                test_error(get_pointer_type(ptr) == pointer_unallocated, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_unallocated, a zwróciła %d", get_pointer_type(ptr));

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 75: Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej niewłaściwego wskaźnika
//
void UTEST75(void)
{
    // informacje o teście
    test_start(75, "Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej niewłaściwego wskaźnika", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                char *ptr = heap_realloc(NULL, 153);

                test_error(ptr != NULL, "Funkcja heap_realloc() powinna zwrócić adres pamięci przydzielonej użytkownikowi");
                test_error(get_pointer_type(ptr) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr));

                void *ptr1 = heap_realloc(ptr + 80, 153);

                test_error(ptr1 == NULL, "Funkcja heap_realloc() powinna zwrócić wartość NULL");
                test_error(get_pointer_type(ptr) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr));
        
                ptr1 = heap_realloc(ptr - 51, 153);

                test_error(ptr1 == NULL, "Funkcja heap_realloc() powinna zwrócić wartość NULL");
                test_error(get_pointer_type(ptr) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr));

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 76: Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania zmniejszenia rozmiaru pamięci
//
void UTEST76(void)
{
    // informacje o teście
    test_start(76, "Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania zmniejszenia rozmiaru pamięci", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                int status = heap_setup();
                test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                unsigned char values[161];
                
                for (int i = 0; i < 161; ++i)
                    values[i] = rand() % 255;

                char *ptr = heap_realloc(NULL, 161);
                char *ptr2 = heap_realloc(NULL, 161);

                test_error(ptr != NULL, "Funkcja heap_realloc() powinna zwrócić adres pamięci przydzielonej użytkownikowi");
                test_error(get_pointer_type(ptr) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr));

                test_error(ptr2 != NULL, "Funkcja heap_realloc() powinna zwrócić adres pamięci przydzielonej użytkownikowi");
                test_error(get_pointer_type(ptr2) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr2));

                memcpy(ptr, values, 161);

                void *ptr1 = heap_realloc(ptr, 80);

                test_error(ptr1 == ptr, "Funkcja heap_realloc() powinna zwrócić ten sam adres, który został do niej przekazany");
                test_error(memcmp(ptr, values, 80) == 0, "Funkcja heap_realloc() nie powinna modyfikować obszaru pamięci użytkownika");

                test_error(get_pointer_type(ptr + 80) == pointer_inside_fences, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_inside_fences, a zwróciła %d", get_pointer_type(ptr + 80));

                 int i = 80;

                char temp = ptr[i];
                ptr[i] += 14;

                status = heap_validate();
                test_error(status == 1, "Funkcja heap_validate() powinna zwrócić wartość 1, a zwróciła na %d", status);

                ptr[i] = temp;

                status = heap_validate();
                test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                while (get_pointer_type(ptr + i) == pointer_inside_fences) ++i;

                test_error(get_pointer_type(ptr + i) == pointer_unallocated, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_unallocated, a zwróciła %d", get_pointer_type(ptr + i));

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
            
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 77: Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania tego samego rozmiaru pamięci, który zajmował poprzednio
//
void UTEST77(void)
{
    // informacje o teście
    test_start(77, "Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania tego samego rozmiaru pamięci, który zajmował poprzednio", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                 int status = heap_setup();
                 test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 unsigned char values[164];

                 for (int i = 0; i < 164; ++i)
                     values[i] = rand() % 255;

                 char *ptr = heap_realloc(NULL, 164);
                 char *ptr2 = heap_realloc(NULL, 164);

                 test_error(ptr != NULL, "Funkcja heap_realloc() powinna zwrócić adres pamięci przydzielonej użytkownikowi");
                 test_error(get_pointer_type(ptr) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr));

                 test_error(ptr2 != NULL, "Funkcja heap_realloc() powinna zwrócić adres pamięci przydzielonej użytkownikowi");
                 test_error(get_pointer_type(ptr2) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr2));

                 memcpy(ptr, values, 164);

                 void *ptr1 = heap_realloc(ptr, 164);

                 test_error(ptr1 == ptr, "Funkcja heap_realloc() powinna zwrócić ten sam adres, który został do niej przekazany");
                 test_error(memcmp(ptr, values, 164) == 0, "Funkcja heap_realloc() nie powinna modyfikować obszaru pamięci użytkownika");

                 test_error(get_pointer_type(ptr + 164) == pointer_inside_fences, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_inside_fences, a zwróciła %d", get_pointer_type(ptr + 164));

                  int i = 164;

                 char temp = ptr[i];
                 ptr[i] += 14;

                 status = heap_validate();
                 test_error(status == 1, "Funkcja heap_validate() powinna zwrócić wartość 1, a zwróciła na %d", status);

                 ptr[i] = temp;

                 status = heap_validate();
                 test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);

             
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 78: Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania większego rozmiaru pamięci, który zajmował poprzednio
//
void UTEST78(void)
{
    // informacje o teście
    test_start(78, "Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania większego rozmiaru pamięci, który zajmował poprzednio", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                 int status = heap_setup();
                 test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 unsigned char values[157];

                 for (int i = 0; i < 157; ++i)
                     values[i] = rand() % 255;

                 char *ptr = heap_realloc(NULL, 157);

                 test_error(ptr != NULL, "Funkcja heap_realloc() powinna zwrócić adres pamięci przydzielonej użytkownikowi");
                 test_error(get_pointer_type(ptr) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr));

                 memcpy(ptr, values, 157);

                 void *ptr1 = heap_realloc(ptr, 879);

                 test_error(ptr1 == ptr, "Funkcja heap_realloc() powinna zwrócić ten sam adres, który został do niej przekazany");
                 test_error(memcmp(ptr, values, 157) == 0, "Funkcja heap_realloc() nie powinna modyfikować obszaru pamięci użytkownika");

                 test_error(get_pointer_type(ptr + 879) == pointer_inside_fences, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_inside_fences, a zwróciła %d", get_pointer_type(ptr + 164));

                  int i = 879;

                 char temp = ptr[i];
                 ptr[i] += 14;

                 status = heap_validate();
                 test_error(status == 1, "Funkcja heap_validate() powinna zwrócić wartość 1, a zwróciła na %d", status);

                 ptr[i] = temp;

                 status = heap_validate();
                 test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
             
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 79: Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania większego rozmiaru pamięci, który zajmował poprzednio
//
void UTEST79(void)
{
    // informacje o teście
    test_start(79, "Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania większego rozmiaru pamięci, który zajmował poprzednio", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                 int status = heap_setup();
                 test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 unsigned char values[131];

                 for (int i = 0; i < 131; ++i)
                     values[i] = rand() % 255;

                 char *ptr = heap_realloc(NULL, 131);

                 test_error(ptr != NULL, "Funkcja heap_realloc() powinna zwrócić adres pamięci przydzielonej użytkownikowi");
                 test_error(get_pointer_type(ptr) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr));

                 memcpy(ptr, values, 131);

                 void *ptr1 = heap_realloc(ptr, 10231252);

                 test_error(ptr1 == ptr, "Funkcja heap_realloc() powinna zwrócić ten sam adres, który został do niej przekazany");
                 test_error(memcmp(ptr, values, 131) == 0, "Funkcja heap_realloc() nie powinna modyfikować obszaru pamięci użytkownika");

                 test_error(get_pointer_type(ptr + 10231252) == pointer_inside_fences, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_inside_fences, a zwróciła %d", get_pointer_type(ptr + 164));

                  int i = 10231252;

                 char temp = ptr[i];
                 ptr[i] += 14;

                 status = heap_validate();
                 test_error(status == 1, "Funkcja heap_validate() powinna zwrócić wartość 1, a zwróciła na %d", status);

                 ptr[i] = temp;

                 status = heap_validate();
                 test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
             
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 80: Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania większego rozmiaru pamięci, który zajmował poprzednio
//
void UTEST80(void)
{
    // informacje o teście
    test_start(80, "Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania większego rozmiaru pamięci, który zajmował poprzednio", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                  int status = heap_setup();
                  test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                  unsigned char values[190];

                  for (int i = 0; i < 190; ++i)
                      values[i] = rand() % 255;

                  char *ptr1 = heap_realloc(NULL, 190);
                  char *ptr2 = heap_realloc(NULL, 1292);
                  char *ptr3 = heap_realloc(NULL, 140);
                  char *ptr4 = heap_realloc(NULL, 187);

                  test_error(get_pointer_type(ptr1) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr1));
                  test_error(get_pointer_type(ptr2) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr2));
                  test_error(get_pointer_type(ptr3) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr3));
                  test_error(get_pointer_type(ptr4) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr4));

                  heap_free(ptr2);
                
                  ptr2 = heap_realloc(NULL, 190);
                
                  heap_free(ptr3);

                  memcpy(ptr2, values, 190);

                  char *ptr5 = heap_realloc(ptr2, 1463);

                  test_error(ptr5 == ptr2, "Funkcja heap_realloc() powinna zwrócić ten sam adres, który został do niej przekazany");
                  test_error(memcmp(ptr2, values, 190) == 0, "Funkcja heap_realloc() nie powinna modyfikować obszaru pamięci użytkownika");

                  test_error(get_pointer_type(ptr2 + 1463) == pointer_inside_fences, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_inside_fences, a zwróciła %d", get_pointer_type(ptr2 + 1463));

                  status = heap_validate();
                  test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
              
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 81: Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania większego rozmiaru pamięci, który zajmował poprzednio
//
void UTEST81(void)
{
    // informacje o teście
    test_start(81, "Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania większego rozmiaru pamięci, który zajmował poprzednio", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                  int status = heap_setup();
                  test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                  unsigned char values[185];

                  for (int i = 0; i < 185; ++i)
                      values[i] = rand() % 255;

                  char *ptr1 = heap_realloc(NULL, 185);
                  char *ptr2 = heap_realloc(NULL, 1398);
                  char *ptr3 = heap_realloc(NULL, 178);
                  char *ptr4 = heap_realloc(NULL, 116);

                  test_error(get_pointer_type(ptr1) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr1));
                  test_error(get_pointer_type(ptr2) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr2));
                  test_error(get_pointer_type(ptr3) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr3));
                  test_error(get_pointer_type(ptr4) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr4));

                  heap_free(ptr2);

                  ptr2 = heap_realloc(NULL, 185);

                  heap_free(ptr3);

                  memcpy(ptr2, values, 185);

                  char *ptr5 = heap_realloc(ptr2, 1430);

                  test_error(ptr5 == ptr2, "Funkcja heap_realloc() powinna zwrócić ten sam adres, który został do niej przekazany");
                  test_error(memcmp(ptr2, values, 185) == 0, "Funkcja heap_realloc() nie powinna modyfikować obszaru pamięci użytkownika");

                  test_error(get_pointer_type(ptr2 + 1430) == pointer_inside_fences, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_inside_fences, a zwróciła %d", get_pointer_type(ptr2 + 1430));

                  status = heap_validate();
                  test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
              
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 82: Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania większego rozmiaru pamięci, który zajmował poprzednio
//
void UTEST82(void)
{
    // informacje o teście
    test_start(82, "Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania większego rozmiaru pamięci, który zajmował poprzednio", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                  int status = heap_setup();
                  test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                  unsigned char values[200];

                  for (int i = 0; i < 200; ++i)
                      values[i] = rand() % 255;

                  char *ptr1 = heap_realloc(NULL, 200);
                  char *ptr2 = heap_realloc(NULL, 1156);
                  char *ptr3 = heap_realloc(NULL, 153);
                  char *ptr4 = heap_realloc(NULL, 103);

                  test_error(get_pointer_type(ptr1) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr1));
                  test_error(get_pointer_type(ptr2) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr2));
                  test_error(get_pointer_type(ptr3) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr3));
                  test_error(get_pointer_type(ptr4) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr4));

                  heap_free(ptr2);

                  ptr2 = heap_realloc(NULL, 200);

                  heap_free(ptr3);

                  memcpy(ptr2, values, 200);

                  char *ptr5 = heap_realloc(ptr2, 3707);

                  test_error(ptr5 != ptr2, "Funkcja heap_realloc() powinna zwrócić ten sam adres, który został do niej przekazany");
                  test_error(memcmp(ptr5, values, 200) == 0, "Funkcja heap_realloc() nie powinna modyfikować obszaru pamięci użytkownika");

                  test_error(get_pointer_type(ptr5 + 3707) == pointer_inside_fences, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_inside_fences, a zwróciła %d", get_pointer_type(ptr5 + 3707));
                  test_error(get_pointer_type(ptr2) == pointer_unallocated, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_unallocated, a zwróciła %d", get_pointer_type(ptr2));

                  status = heap_validate();
                  test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
              
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 83: Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania większego rozmiaru pamięci, który zajmował poprzednio
//
void UTEST83(void)
{
    // informacje o teście
    test_start(83, "Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania większego rozmiaru pamięci, który zajmował poprzednio", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                  int status = heap_setup();
                  test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                  unsigned char values[164];

                  for (int i = 0; i < 164; ++i)
                      values[i] = rand() % 255;

                  char *ptr1 = heap_realloc(NULL, 164);
                  char *ptr2 = heap_realloc(NULL, 1729);
                  char *ptr3 = heap_realloc(NULL, 180);
                  char *ptr4 = heap_realloc(NULL, 167);

                  test_error(get_pointer_type(ptr1) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr1));
                  test_error(get_pointer_type(ptr2) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr2));
                  test_error(get_pointer_type(ptr3) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr3));
                  test_error(get_pointer_type(ptr4) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr4));

                  heap_free(ptr2);

                  ptr2 = heap_realloc(NULL, 164);

                  heap_free(ptr3);

                  memcpy(ptr2, values, 164);

                  char *ptr5 = heap_realloc(ptr2, 67236104);

                  test_error(ptr5 != ptr2, "Funkcja heap_realloc() powinna zwrócić ten sam adres, który został do niej przekazany");
                  test_error(memcmp(ptr2, values, 164) == 0, "Funkcja heap_realloc() nie powinna modyfikować obszaru pamięci użytkownika");

                  test_error(get_pointer_type(ptr2) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr2));
                  test_error(get_pointer_type(ptr5) == pointer_null, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_null, a zwróciła %d", get_pointer_type(ptr5));

                  status = heap_validate();
                  test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
              
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 84: Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania większego rozmiaru pamięci, który zajmował poprzednio
//
void UTEST84(void)
{
    // informacje o teście
    test_start(84, "Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania większego rozmiaru pamięci, który zajmował poprzednio", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                  int status = heap_setup();
                  test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                  unsigned char values[110];

                  for (int i = 0; i < 110; ++i)
                      values[i] = rand() % 255;

                  char *ptr1 = heap_realloc(NULL, 100);
                  char *ptr2 = heap_realloc(NULL, 1134);
                  char *ptr3 = heap_realloc(NULL, 187);
                  char *ptr4 = heap_realloc(NULL, 110);

                  test_error(get_pointer_type(ptr1) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr1));
                  test_error(get_pointer_type(ptr2) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr2));
                  test_error(get_pointer_type(ptr3) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr3));
                  test_error(get_pointer_type(ptr4) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr4));

                  memcpy(ptr4, values, 110);

                  char *ptr5 = heap_realloc(ptr4, 67487570);

                  test_error(ptr5 == NULL, "Funkcja heap_realloc() powinna zwrócić NULL");
                  test_error(memcmp(ptr4, values, 110) == 0, "Funkcja heap_realloc() nie powinna modyfikować obszaru pamięci użytkownika");

                  test_error(get_pointer_type(ptr4) == pointer_valid, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_valid, a zwróciła %d", get_pointer_type(ptr2));
                  test_error(get_pointer_type(ptr5) == pointer_null, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_null, a zwróciła %d", get_pointer_type(ptr5));

                  test_error(get_pointer_type(ptr4 + 110) == pointer_inside_fences, "Funkcja get_pointer_type() powinna zwrócić wartość pointer_inside_fences, a zwróciła %d", get_pointer_type(ptr4 + 110));

                  status = heap_validate();
                  test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);
              
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 85: Sprawdzanie poprawności działania funkcji heap_realloc
//
void UTEST85(void)
{
    // informacje o teście
    test_start(85, "Sprawdzanie poprawności działania funkcji heap_realloc", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                   srand (time(NULL));

                   int status = heap_setup();
                   test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                   char *ptr[3121];
                   int ptr_state[3121] = {0};

                   int is_allocated = 0;

                   for (int i = 0; i < 3121; ++i)
                   {
                     int rand_value = rand() % 100;
                     if (rand_value < 33)
                     {
                       for (int j = 0; j < 3121; ++j)
                         if (ptr_state[j] == 0)
                         {
                           ptr_state[j] = 1;
                           ptr[j] = heap_realloc(NULL, rand() % 1000 + 500);  
                           is_allocated++;
                           break;
                         }
                     }
                     else if (rand_value < 66)
                     {
                       if (is_allocated)
                       {
                          int to_reallocate = rand() % is_allocated;
                          for (int j = 0; j < 3121; ++j)
                           {
                               if (ptr_state[j] == 1 && !to_reallocate)
                               {
                                   if (rand() % 100 < 50)
                                       ptr[j] = heap_realloc(ptr[j], rand() % 1000 + 500);
                                   else
                                       ptr[j] = heap_realloc(ptr[j], rand() % 10000 + 5000);    
                                   break;
                               }
                               to_reallocate--;
                           }
                       }
                     }
                     else
                     {
                       if (is_allocated)
                       {
                         int to_free = rand() % is_allocated;
                          for (int j = 0; j < 3121; ++j)
                           {
                               if (ptr_state[j] == 1 && !to_free)
                               {
                                 ptr_state[j] = 0;
                                 is_allocated--;
                                 heap_realloc(ptr[j], 0);
                                 break;
                               }
                               to_free--;
                           }
                       }
                     }
                     status = heap_validate();
                     test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła na %d", status);           
                   }

                   for (int j = 0; j < 3121; ++j)
                     if (ptr_state[j] == 1)
                         heap_realloc(ptr[j], 0);

                   test_error(heap_get_largest_used_block_size() == 0, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 0, a zwróciła na %llu", heap_get_largest_used_block_size());

                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);

             
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}

//
//  Test 86: Sprawdzanie poprawności działania funkcji heap_realloc, heap_malloc, heap_calloc i heap_free
//
void UTEST86(void)
{
    // informacje o teście
    test_start(86, "Sprawdzanie poprawności działania funkcji heap_realloc, heap_malloc, heap_calloc i heap_free", __LINE__);

    // uwarunkowanie zasobów - pamięci, itd...
    test_file_write_limit_setup(33554432);
    rldebug_reset_limits();
    
    //
    // -----------
    //
    
                   srand (time(NULL));

                   int status = heap_setup();
                   test_error(status == 0, "Funkcja heap_setup() powinna zwrócić wartość 0, a zwróciła na %d", status);

                   char *ptr[720];
                   int ptr_state[720] = {0};

                   int is_allocated = 0;

                   for (int i = 0; i < 720; ++i)
                   {
                     int rand_value = rand() % 100;
                     if (rand_value < 16)
                     {
                       for (int j = 0; j < 720; ++j)
                         if (ptr_state[j] == 0)
                         {
                           ptr_state[j] = 1;
                           ptr[j] = heap_realloc(NULL, rand() % 100 + 50);  
                           is_allocated++;
                           break;
                         }
                     }
                     else if (rand_value < 33)
                     {
                       if (is_allocated)
                       {
                          int to_reallocate = rand() % is_allocated;
                          for (int j = 0; j < 720; ++j)
                           {
                               if (ptr_state[j] == 1 && !to_reallocate)
                               {
                                   if (rand() % 100 < 50)
                                       ptr[j] = heap_realloc(ptr[j], rand() % 100 + 50);
                                   else
                                       ptr[j] = heap_realloc(ptr[j], rand() % 1000 + 500);    
                                   break;
                               }
                               to_reallocate--;
                           }
                       }
                     }
                     else if (rand_value < 50)
                     {
                       if (is_allocated)
                       {
                         int to_free = rand() % is_allocated;
                          for (int j = 0; j < 720; ++j)
                           {
                               if (ptr_state[j] == 1 && !to_free)
                               {
                                 ptr_state[j] = 0;
                                 is_allocated--;
                                 heap_realloc(ptr[j], 0);
                                 break;
                               }
                               to_free--;
                           }
                       }
                     }
                     else if (rand_value < 66)
                     {
                       for (int j = 0; j < 720; ++j)
                         if (ptr_state[j] == 0)
                         {
                           ptr_state[j] = 1;
                           ptr[j] = heap_malloc(rand() % 100 + 50);  
                           is_allocated++;
                           break;
                         }
                     }
                     else if (rand_value < 83)
                     {
                       for (int j = 0; j < 720; ++j)
                         if (ptr_state[j] == 0)
                         {
                           ptr_state[j] = 1;
                           ptr[j] = heap_calloc(rand() % 100 + 50, rand() % 10 + 1);  
                           is_allocated++;
                           break;
                         }
                     }     
                     else
                     {
                       if (is_allocated)
                       {
                         int to_free = rand() % is_allocated;
                          for (int j = 0; j < 720; ++j)
                           {
                               if (ptr_state[j] == 1 && !to_free)
                               {
                                 ptr_state[j] = 0;
                                 is_allocated--;
                                 heap_free(ptr[j]);
                                 break;
                               }
                               to_free--;
                           }
                       }
                     }
                     status = heap_validate();
                     test_error(status == 0, "Funkcja heap_validate() powinna zwrócić wartość 0, a zwróciła %d", status);           
                   }

                   heap_show();
                   for (int j = 0; j < 720; ++j)
                     if (ptr_state[j] == 1)
                         heap_realloc(ptr[j], 0);

                   test_error(heap_get_largest_used_block_size() == 0, "Funkcja heap_get_largest_used_block_size() powinna zwrócić wartość 0, a zwróciła na %llu", heap_get_largest_used_block_size());

                 printf("Po reallocu!\n");
                 heap_show();
                 status = custom_sbrk_check_fences_integrity();
                 test_error(status == 0, "Funkcja custom_sbrk_check_fences_integrity() powinna zwrócić wartość 0, a zwróciła na %d. Oznacza to, że alokator nadpisał pamięć, która nie została przydzielona przez system", status);

                 heap_clean();

                 uint64_t reserved_memory = custom_sbrk_get_reserved_memory();
                 test_error(reserved_memory == 0, "Funkcja custom_sbrk_get_reserved_memory() powinna zwrócić wartość 0, a zwróciła na %llu. Po wywołaniu funkcji heap_clean cała pamięć zarezerwowana przez alokator powinna być zwrócona do systemu", reserved_memory);

             
    //
    // -----------
    //

    // przywrócenie podstawowych parametów przydzielania zasobów (jeśli to tylko możliwe)
    rldebug_reset_limits();
    test_file_write_limit_restore();
    
    test_ok();
}




enum run_mode_t { rm_normal_with_rld = 0, rm_unit_test = 1, rm_main_test = 2 };

int __wrap_main(volatile int _argc, char** _argv, char** _envp)
{
    int volatile vargc = _argc;
    char ** volatile vargv = _argv, ** volatile venvp = _envp;
	volatile enum run_mode_t run_mode = rm_unit_test; // -1
	volatile int selected_test = -1;

    if (vargc > 1)
	{
	    char* smode = strtok(vargv[1], ",");
	    char* stest = strtok(NULL, "");
		char *errptr = NULL;
		run_mode = (enum run_mode_t)strtol(smode, &errptr, 10);
		if (*errptr == '\x0')
		{
			memmove(vargv + 1, vargv + 2, sizeof(char*) * (vargc - 1));
			vargc--;

			if (stest != NULL)
			{
			    int val = (int)strtol(stest, &errptr, 10);
			    if (*errptr == '\x0')
			        selected_test = val;
			}
		}
	}

    // printf("runmode=%d; selected_test=%d\n", run_mode, selected_test);

    // inicjuj testy jednostkowe
    unit_test_init(run_mode, "unit_test_v2.c");
    test_limit_init();
    rldebug_set_reported_severity_level(MSL_FAILURE);

    if (run_mode == rm_normal_with_rld)
    {
        // konfiguracja ograniczników
        rldebug_reset_limits();
        

        // uruchom funkcję main Studenta a potem wyświetl podsumowanie sterty i zasobów
        volatile int ret_code = rdebug_call_main(tested_main, vargc, vargv, venvp);

        rldebug_reset_limits();
        

        int leaks_detected = rldebug_show_leaked_resources(0);
        if (leaks_detected)
            raise(SIGHEAP);

        return ret_code;
    }

    
    if (run_mode == rm_unit_test)
    {
        test_title("Testy jednostkowe");

        void (*pfcn[])(void) =
        { 
            UTEST1, // Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej wartości 0
            UTEST2, // Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń obecna na stercie
            UTEST3, // Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku pierwszej próby zaalokowania przestrzeni mniejszej niż przestrzeń obecna na stercie
            UTEST4, // Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni mniejszej niż przestrzeń obecna na stercie, w przypadku przydzielenia wcześniej pamięci użytkownikowi
            UTEST5, // Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni mniejszej niż przestrzeń obecna na stercie (żądana pamięć wymaga zwiększenia limitu pamięci przydzielonego przez system), w przypadku przydzielenia wcześniej pamięci użytkownikowi
            UTEST6, // Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń, która może być przydzielona przez system (żądana pamięć wymaga zwiększenia limitu pamięci przydzielonego przez system), w przypadku przydzielenia wcześniej pamięci użytkownikowi
            UTEST7, // Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeń mniejszej niż przestrzeń poprzednio zwolniona
            UTEST8, // Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni równej przestrzeni poprzednio zwolnionej
            UTEST9, // Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni mniejszej niż przestrzeń poprzednio zwolniona
            UTEST10, // Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni równej przestrzeń poprzednio zwolnionej
            UTEST11, // Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń poprzednio zwolnionej
            UTEST12, // Sprawdzanie poprawności działania funkcji heap_malloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń poprzednio zwolnionej
            UTEST13, // Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej wartości 0
            UTEST14, // Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej wartości 0
            UTEST15, // Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej wartości 0
            UTEST16, // Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń obecna na stercie
            UTEST17, // Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń obecna na stercie
            UTEST18, // Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku pierwszej próby zaalokowania przestrzeni mniejszej niż przestrzeń obecna na stercie
            UTEST19, // Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku pierwszej próby zaalokowania przestrzeni mniejszej niż przestrzeń obecna na stercie
            UTEST20, // Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni mniejszej niż przestrzeń obecna na stercie, w przypadku przydzielenia wcześniej pamięci użytkownikowi
            UTEST21, // Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni mniejszej niż przestrzeń obecna na stercie (żądana pamięć wymaga zwiększenia limitu pamięci przydzielonego przez system), w przypadku przydzielenia wcześniej pamięci użytkownikowi
            UTEST22, // Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń, która może być przydzielona przez system (żądana pamięć wymaga zwiększenia limitu pamięci przydzielonego przez system), w przypadku przydzielenia wcześniej pamięci użytkownikowi
            UTEST23, // Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeń mniejszej niż przestrzeń poprzednio zwolniona
            UTEST24, // Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni równej przestrzeni poprzednio zwolnionej
            UTEST25, // Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni mniejszej niż przestrzeń poprzednio zwolniona
            UTEST26, // Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni równej przestrzeni poprzednio zwolnionej
            UTEST27, // Sprawdzanie poprawności działania funkcji heap_calloc - test sprawdza poprawność działania funkcji w przypadku próby zaalokowania przestrzeni większej niż przestrzeń poprzednio zwolnionej
            UTEST28, // Sprawdzanie poprawności działania funkcji heap_get_largest_used_block_size
            UTEST29, // Sprawdzanie poprawności działania funkcji heap_get_largest_used_block_size
            UTEST30, // Sprawdzanie poprawności działania funkcji heap_get_largest_used_block_size
            UTEST31, // Sprawdzanie poprawności działania funkcji heap_get_largest_used_block_size
            UTEST32, // Sprawdzanie poprawności działania funkcji heap_get_largest_used_block_size
            UTEST33, // Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku przekazania do niej niepoprawnego wskaźnika lub wskaźnika sprzed inicjalizacji sterty
            UTEST34, // Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku przekazania do niej niepoprawnego wskaźnika
            UTEST35, // Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku przekazania do niej niepoprawnego wskaźnika
            UTEST36, // Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku przekazania do niej niepoprawnego wskaźnika
            UTEST37, // Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku przekazania do niej niepoprawnego wskaźnika
            UTEST38, // Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia dwóch bloków pamięci sąsiadujących ze sobą
            UTEST39, // Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia dwóch bloków pamięci sąsiadujących ze sobą i zaalokowanie w tym miejscu nowej pamięci o rozmiarze sumy dwóch zwolnionych bloków
            UTEST40, // Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia dwóch bloków pamięci sąsiadujących ze sobą
            UTEST41, // Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia dwóch bloków pamięci sąsiadujących ze sobą i zaalokowanie w tym miejscu nowej pamięci o rozmiarze sumy dwóch zwolnionych bloków
            UTEST42, // Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia trzech bloków pamięci sąsiadujących ze sobą
            UTEST43, // Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia trzech bloków pamięci sąsiadujących ze sobą i zaalokowanie w tym miejscu nowej pamięci o rozmiarze sumy dwóch zwolnionych bloków
            UTEST44, // Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia bloku pamięci, zaalokowania w to miejsce mniejszego bloku, zwolnienia go i zaalokowania ponownie większego bloku
            UTEST45, // Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia trzech bloków pamięci sąsiadujących ze sobą i zaalokowanie w tym miejscu nowej pamięci o rozmiarze sumy dwóch zwolnionych bloków
            UTEST46, // Sprawdzanie poprawności działania funkcji heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia trzech bloków pamięci sąsiadujących ze sobą i zaalokowanie w tym miejscu nowej pamięci o rozmiarze sumy dwóch zwolnionych bloków
            UTEST47, // Sprawdzanie poprawności działania funkcji heap_malloc, heap_calloc i heap_free - test sprawdza poprawność działania funkcji w przypadku zwolnienia trzech bloków pamięci sąsiadujących ze sobą i zaalokowanie w tym miejscu nowej pamięci o rozmiarze sumy dwóch zwolnionych bloków
            UTEST48, // Sprawdzanie poprawności działania funkcji heap_malloc i heap_free
            UTEST49, // Sprawdzanie poprawności działania funkcji get_pointer_type
            UTEST50, // Sprawdzanie poprawności działania funkcji get_pointer_type
            UTEST51, // Sprawdzanie poprawności działania funkcji get_pointer_type
            UTEST52, // Sprawdzanie poprawności działania funkcji get_pointer_type
            UTEST53, // Sprawdzanie poprawności działania funkcji get_pointer_type
            UTEST54, // Sprawdzanie poprawności działania funkcji get_pointer_type
            UTEST55, // Sprawdzanie poprawności działania funkcji get_pointer_type
            UTEST56, // Sprawdzanie poprawności działania funkcji get_pointer_type
            UTEST57, // Sprawdzanie poprawności działania funkcji get_pointer_type
            UTEST58, // Sprawdzanie poprawności działania funkcji get_pointer_type
            UTEST59, // Sprawdzanie poprawności działania funkcji get_pointer_type
            UTEST60, // Sprawdzanie poprawności działania funkcji get_pointer_type
            UTEST61, // Sprawdzanie poprawności działania funkcji get_pointer_type
            UTEST62, // Sprawdzanie poprawności działania funkcji get_pointer_type
            UTEST63, // Sprawdzanie poprawności działania funkcji heap_validate
            UTEST64, // Sprawdzanie poprawności działania funkcji heap_validate
            UTEST65, // Sprawdzanie poprawności działania funkcji heap_validate
            UTEST66, // Sprawdzanie poprawności działania funkcji heap_validate
            UTEST67, // Sprawdzanie poprawności działania funkcji heap_validate
            UTEST68, // Sprawdzanie poprawności działania funkcji heap_validate
            UTEST69, // Sprawdzanie poprawności działania funkcji heap_validate
            UTEST70, // Sprawdzanie poprawności działania funkcji heap_validate
            UTEST71, // Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej wartości 0
            UTEST72, // Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku niezainicjowania sterty
            UTEST73, // Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej poprawnej wartości
            UTEST74, // Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej wartości 0
            UTEST75, // Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku przekazania do niej niewłaściwego wskaźnika
            UTEST76, // Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania zmniejszenia rozmiaru pamięci
            UTEST77, // Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania tego samego rozmiaru pamięci, który zajmował poprzednio
            UTEST78, // Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania większego rozmiaru pamięci, który zajmował poprzednio
            UTEST79, // Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania większego rozmiaru pamięci, który zajmował poprzednio
            UTEST80, // Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania większego rozmiaru pamięci, który zajmował poprzednio
            UTEST81, // Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania większego rozmiaru pamięci, który zajmował poprzednio
            UTEST82, // Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania większego rozmiaru pamięci, który zajmował poprzednio
            UTEST83, // Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania większego rozmiaru pamięci, który zajmował poprzednio
            UTEST84, // Sprawdzanie poprawności działania funkcji heap_realloc - test sprawdza poprawność działania funkcji w przypadku żądania większego rozmiaru pamięci, który zajmował poprzednio
            UTEST85, // Sprawdzanie poprawności działania funkcji heap_realloc
            UTEST86, // Sprawdzanie poprawności działania funkcji heap_realloc, heap_malloc, heap_calloc i heap_free
            NULL
        };

        for (int idx = 0; pfcn[idx] != NULL && !test_get_session_termination_flag(); idx++)
        {
            if (selected_test == -1 || selected_test == idx + 1)
                pfcn[idx]();

            // limit niezaliczonych testów, po jakim testy jednostkowe zostaną przerwane
            if (test_session_get_fail_count() >= 1000)
                test_terminate_session();
        }


        test_title("RLDebug :: Analiza wycieku zasobów");
        // sprawdź wycieki pamięci
        int leaks_detected = rldebug_show_leaked_resources(1);
        test_set_session_leaks(leaks_detected);

        // poinformuj serwer Mrówka o wyniku testu - podsumowanie
        test_title("Podsumowanie");
        if (selected_test == -1)
            test_summary(86); // wszystkie testy muszą zakończyć się sukcesem
        else
            test_summary(1); // tylko jeden (selected_test) test musi zakończyć się  sukcesem
        return EXIT_SUCCESS;
    }
    

    if (run_mode == rm_main_test)
    {
        test_title("Testy funkcji main()");

        void (*pfcn[])(int, char**, char**) =
        { 
            NULL
        };

        for (volatile int idx = 0; pfcn[idx] != NULL && !test_get_session_termination_flag(); idx++)
        {
            if (selected_test == -1 || selected_test == idx + 1)
                pfcn[idx](vargc, vargv, venvp);

            // limit niezaliczonych testów, po jakim testy jednostkowe zostaną przerwane
            if (test_session_get_fail_count() >= 1000)
                test_terminate_session();
        }


        test_title("RLDebug :: Analiza wycieku zasobów");
        // sprawdź wycieki pamięci
        int leaks_detected = rldebug_show_leaked_resources(1);
        test_set_session_leaks(leaks_detected);

        // poinformuj serwer Mrówka o wyniku testu - podsumowanie
        test_title("Podsumowanie");
        if (selected_test == -1)
            test_summary(0); // wszystkie testy muszą zakończyć się sukcesem
        else
            test_summary(1); // tylko jeden (selected_test) test musi zakończyć się  sukcesem

        return EXIT_SUCCESS;
    }

    printf("*** Nieznana wartość RunMode: %d", (int)run_mode);
    abort();
}