#include <gtest.h>
#include "utmatrix.h"

TEST(TVector, can_create_vector_with_positive_length)
{
    ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
    // максимальный допустимый размер вектора = TVector<int>::max_size
    ASSERT_ANY_THROW(TVector<int> v(TVector<int>::max_size + static_cast<size_t>(1)));
}

TEST(TVector, can_create_huge_vector)
{
    const size_t size = 2000ull * 1000ull * 1000ull * 1000ull;
    const size_t startIndex = size - 10ull;
    TVector<double> v1(size, startIndex);
    ASSERT_NO_THROW(v1.setElement(size - 1ull, 1.0));

    EXPECT_EQ(size, v1.getSize());
    EXPECT_EQ(1.0, v1.getElement(size - 1ull));

}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
    ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
    ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
    TVector<int> v(10);

    ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
    TVector<int> v(2);
    v[0] = 1;
    v[1] = 2;
    TVector<int> v1(v);
    EXPECT_EQ(v, v1);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
    TVector<int> v(2);
    v[0] = 1;
    v[1] = 2;
    TVector<int> v1(v);
    EXPECT_NE(&v, &v1);
}

TEST(TVector, can_get_size)
{
    TVector<int> v(4);
    EXPECT_EQ(4, v.getSize());
}

TEST(TVector, can_get_start_index)
{
    TVector<int> v(4, 2);
    EXPECT_EQ(2, v.getStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
    TVector<int> v(4);
    v[0] = 4;
    EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
    TVector<int> v(4);
    ASSERT_ANY_THROW(v.setElement(-1, 5));
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
    TVector<int> v(4);
    ASSERT_ANY_THROW(v.setElement(10, 5));
}

TEST(TVector, can_assign_vector_to_itself)
{
    TVector<int> v(4);
    ASSERT_NO_THROW(v = v);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
    int size = 2;
    TVector<int> v1(size), v2(size);
    v1[0] = 1;
    v1[1] = 2;
    v2 = v1;
    EXPECT_EQ(v1, v2);
}

TEST(TVector, assign_operator_change_vector_size)
{
    TVector<int> v1(1), v2(2);
    v1[0] = 1;
    v2 = v1;
    EXPECT_EQ(v1.getSize(), v2.getSize());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
    TVector<int> v1(1), v2(2);
    v1[0] = 1;
    v2 = v1;
    EXPECT_EQ(v1, v2);
}

TEST(TVector, compare_equal_vectors_return_true)
{
    TVector<int> v1(2), v2(2);
    v1[0] = 1;
    v1[1] = 2;
    v2[0] = 1;
    v2[1] = 2;
    EXPECT_EQ(v1, v2);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
    TVector<int> v(2);
    v[0] = 1;
    v[1] = 2;
    EXPECT_EQ(v, v);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
    TVector<int> v1(1), v2(2);
    v1[0] = 1;
    v2[0] = 1;
    v2[1] = 2;
    EXPECT_NE(v1, v2);
}

TEST(TVector, can_add_scalar_to_vector)
{
    TVector<int> v1(2), v2(2);
    v1[0] = 1;
    v1[1] = 2;
    v2[0] = 2;
    v2[1] = 3;
    EXPECT_EQ((v1 + 1), v2);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
    TVector<int> v1(2), v2(2);
    v1[0] = 1;
    v1[1] = 2;
    v2[0] = 0;
    v2[1] = 1;
    EXPECT_EQ((v1 - 1), v2);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
    TVector<int> v1(2), v2(2);
    v1[0] = 1;
    v1[1] = 2;
    v2[0] = 2;
    v2[1] = 4;
    EXPECT_EQ((v1 * 2), v2);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
    TVector<int> v1(2), v2(2), res(2);
    v1[0] = 1;
    v1[1] = 2;
    v2[0] = 2;
    v2[1] = 4;
    res[0] = v1[0] + v2[0];
    res[1] = v1[1] + v2[1];
    EXPECT_EQ((v1 + v2), res);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
    TVector<int> v1(1), v2(2);
    v1[0] = 1;
    v2[0] = 2;
    v2[1] = 4;
    ASSERT_ANY_THROW(v1 + v2);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
    TVector<int> v1(2), v2(2), res(2);
    v1[0] = 1;
    v1[1] = 2;
    v2[0] = 2;
    v2[1] = 4;
    res[0] = v1[0] - v2[0];
    res[1] = v1[1] - v2[1];
    EXPECT_EQ((v1 - v2), res);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
    TVector<int> v1(1), v2(2);
    v1[0] = 1;
    v2[0] = 2;
    v2[1] = 4;
    ASSERT_ANY_THROW(v1 - v2);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
    TVector<int> v1(2), v2(2);
    v1[0] = 1;
    v1[1] = 2;
    v2[0] = 3;
    v2[1] = 4;
    int exp_res = v1[0] * v2[0] + v1[1] * v2[1];
    EXPECT_EQ((v1 * v2), exp_res);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
    TVector<int> v1(1), v2(2);
    v1[0] = 1;
    v2[0] = 2;
    v2[1] = 4;
    ASSERT_ANY_THROW(v1 * v2);
}
