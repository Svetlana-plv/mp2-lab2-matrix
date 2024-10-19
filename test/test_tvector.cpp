#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v1(7);
	TDynamicVector<int> v2(v1);

	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v1(7);
	TDynamicVector<int> v2(v1);

	EXPECT_NE(&v2, &v1);
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(4);

	EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
	TDynamicVector<int> v(4);
	v[0] = 4;

	EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(7);

	ASSERT_ANY_THROW(v.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(7);

	ASSERT_ANY_THROW(v.at(7));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(7);

	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(7);
	TDynamicVector<int> v2(7);

	ASSERT_NO_THROW(v2 = v1);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(7);

	v2 = v1;

	EXPECT_EQ(v1.size(), v2.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(7);

	ASSERT_NO_THROW(v2 = v1);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	int size = 3;
	TDynamicVector<int> v1(size);
	TDynamicVector<int> v2(size);

	for (int i = 0; i < size; i++) {
		v1[i] = i;
		v2[i] = i;
	}

	EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(3);

	EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(5);

	EXPECT_TRUE(v1 != v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	int scalar = 7;
	int size = 3;
	TDynamicVector<int> v1(size);
	TDynamicVector<int> v2(size);

	for (int i = 0; i < size; i++) {
		v1[i] = i;
		v2[i] = i+scalar;
	}
	v1 = v1 + scalar;

	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	int scalar = 7;
	int size = 3;
	TDynamicVector<int> v1(size);
	TDynamicVector<int> v2(size);

	for (int i = 0; i < size; i++) {
		v1[i] = i;
		v2[i] = i - scalar;
	}
	v1 = v1 - scalar;

	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	int scalar = 7;
	int size = 3;
	TDynamicVector<int> v1(size);
	TDynamicVector<int> v2(size);

	for (int i = 0; i < size; i++) {
		v1[i] = i;
		v2[i] = i * scalar;
	}
	v1 = v1 * scalar;

	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	int size = 3;
	TDynamicVector<int> result;
	TDynamicVector<int> v1(size);
	TDynamicVector<int> v2(size);

	for (int i = 0; i < size; i++) {
		v1[i] = i;
		v2[i] = i;
	}
	result = v1 + v2;

	EXPECT_EQ(result, v1*2);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(7);

	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	int size = 3;
	TDynamicVector<int> result;
	TDynamicVector<int> v1(size);
	TDynamicVector<int> v2(size);
	TDynamicVector<int> v(size);

	for (int i = 0; i < size; i++) {
		v1[i] = i;
		v2[i] = i;
	}
	result = v1 - v2;

	EXPECT_EQ(result, v);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(7);

	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	int size = 3;
	int result = 0;
	TDynamicVector<int> v1(size);
	TDynamicVector<int> v2(size);

	for (int i = 0; i < size; i++) {
		v1[i] = 1;
		v2[i] = 1;
	}
	result = v1 * v2;

	EXPECT_EQ(result, size);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(7);

	ASSERT_ANY_THROW(v1 * v2);
}

