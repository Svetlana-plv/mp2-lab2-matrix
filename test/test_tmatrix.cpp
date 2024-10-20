#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
	TDynamicMatrix<int> m(5);

	ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(m1);

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(m1);

	EXPECT_NE(&m1, &m2);
}

TEST(TDynamicMatrix, can_get_size)
{
	int size = 3;
	TDynamicMatrix<int> m(size);

	EXPECT_EQ(m.size(), size);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(3);

	m[1][1] = 7;

	EXPECT_EQ(7, m[1][1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(3);

	ASSERT_ANY_THROW(m.at(-1, -1) = 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(3);

	ASSERT_ANY_THROW(m.at(3, 3) = 1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(3);

	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(3);

	ASSERT_NO_THROW(m1 = m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(5);

	m1 = m2;

	EXPECT_EQ(m1.size(), m2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(5);

	ASSERT_NO_THROW(m1 = m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	int size = 3;
	TDynamicMatrix<int> m1(size);
	TDynamicMatrix<int> m2(size);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m1[i][j] = i;
			m2[i][j] = i;
		}
	}

	EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	int size = 3;
	TDynamicMatrix<int> m(size);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m[i][j] = i;
		}
	}

	EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(5);

	EXPECT_NE(m1, m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(3);

	EXPECT_NO_THROW(m1+m2);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(5);

	ASSERT_ANY_THROW(m1+m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(3);

	EXPECT_NO_THROW(m1 - m2);
}

TEST(TDynamicMatrix, cant_subtract_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(5);

	ASSERT_ANY_THROW(m1 - m2);
}

// Move semantic tests

TEST(TDynamicMatrix, can_move_matrix_using_move_constructor)
{
	TDynamicMatrix<int> m(7);

	ASSERT_NO_THROW(TDynamicMatrix<int> m1(std::move(m)));
}

TEST(TDynamicMatrix, moved_matrix_is_empty_after_using_move_constructor)
{
	TDynamicMatrix<int> m1(7);
	TDynamicMatrix<int> m2(std::move(m1));

	EXPECT_EQ(m1.size(), 0);
}

TEST(TDynamicMatrix, moved_matrix_has_correct_data_after_using_move_constructor)
{
	int size = 7;
	TDynamicMatrix<int> m1(size);
	TDynamicMatrix<int> m2(size);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m1[i][j] = i;
		}
	}
	m2 = m1;

	TDynamicMatrix<int> m3(std::move(m1));

	EXPECT_EQ(m2, m3);
}

TEST(TDynamicMatrix, can_assign_matrix_using_move_operator)
{
	TDynamicMatrix<int> m1(7);
	TDynamicMatrix<int> m2(7);

	ASSERT_NO_THROW(TDynamicMatrix<int> m2 = std::move(m1));
}

TEST(TDynamicMatrix, moved_matrix_is_empty_after_using_move_operator)
{
	TDynamicMatrix<int> m1(7);
	TDynamicMatrix<int> m2;

	m2 = std::move(m1);

	EXPECT_EQ(m1.size(), 0);
}

TEST(TDynamicMatrix, moved_matrix_has_correct_data_after_using_move_operator)
{
	int size = 7;
	TDynamicMatrix<int> m1(size);
	TDynamicMatrix<int> m2(size);
	TDynamicMatrix<int> m3(size);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m1[i][j] = i;
		}
	}
	m2 = m1;

	m3 = std::move(m1);

	EXPECT_EQ(m2, m3);
}

// My tests

TEST(TDynamicMatrix, can_set_and_get_element_using_method_at)
{
	TDynamicMatrix<int> m(3);
	m.at(0, 0) = 7;

	EXPECT_EQ(7, m.at(0, 0));
}

TEST(TDynamicMatrix, compare_matrix_with_not_equal_data_by_operator_not_equal_return_true)
{
	int size = 3;
	TDynamicMatrix<int> m1(size);
	TDynamicMatrix<int> m2(size);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m1[i][j] = i;
			m2[i][j] = i+1;
		}
	}

	EXPECT_TRUE(m1 != m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size_and_data_is_correct)
{
	int size = 3;
	TDynamicMatrix<int> m1(size);
	TDynamicMatrix<int> m2(size);
	TDynamicMatrix<int> result(size);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m1[i][j] = i;
			m2[i][j] = i;
			result[i][j] = i + i;
		}
	}

	EXPECT_EQ(m1 + m2, result);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size_and_data_is_correct)
{
	int size = 3;
	TDynamicMatrix<int> m1(size);
	TDynamicMatrix<int> m2(size);
	TDynamicMatrix<int> result(size);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m1[i][j] = i;
			m2[i][j] = i;
		}
	}

	EXPECT_EQ(m1 - m2, result);
}

TEST(TDynamicMatrix, can_multiply_scalar_by_matrix)
{
	TDynamicMatrix<int> m(3);

	EXPECT_NO_THROW(m*7);
}

TEST(TDynamicMatrix, can_multiply_scalar_by_matrix_and_data_is_correct)
{
	int size = 3;
	int scalar = 5;
	TDynamicMatrix<int> m1(size);
	TDynamicMatrix<int> m2(size);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m1[i][j] = i;
			m2[i][j] = i*scalar;
		}
	}

	EXPECT_EQ(m1*scalar, m2);
}

TEST(TDynamicMatrix, can_multiply_vector_by_matrix)
{
	TDynamicMatrix<int> m(3);
	TDynamicVector<int> v(3);

	EXPECT_NO_THROW(m * v);
}

TEST(TDynamicMatrix, cant_multiply_vector_by_matrix_with_not_equal_sizes)
{
	TDynamicMatrix<int> m(3);
	TDynamicVector<int> v(5);

	EXPECT_ANY_THROW(m * v);
}

TEST(TDynamicMatrix, can_multiply_vector_by_matrix_and_data_is_correct)
{
	int size = 3;
	TDynamicMatrix<int> m(size);
	TDynamicVector<int> v(size);
	TDynamicVector<int> result(size);


	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m[i][j] = 1;
		}
		v[i] = 1;
		result[i] = size;
	}

	EXPECT_EQ(result, m*v);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(3);

	EXPECT_NO_THROW(m1 * m2);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(5);

	ASSERT_ANY_THROW(m1 * m2);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size_and_data_is_correct)
{
	int size = 3;
	TDynamicMatrix<int> m1(size);
	TDynamicMatrix<int> m2(size);
	TDynamicMatrix<int> result(size);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m1[i][j] = 1;
			m2[i][j] = 1;
			result[i][j] = size;
		}
	}
	EXPECT_EQ(result, m1 * m2);
}