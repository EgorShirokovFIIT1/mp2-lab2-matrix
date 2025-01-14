#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrix<int> m(2));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(-10));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
	TDynamicMatrix<int> m(2);

	ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 1;
	TDynamicMatrix<int> m1(m);
	EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 10;
	TDynamicMatrix<int> m1(m);
	m1[0][0] = -10;
	EXPECT_NE(m, m1);

}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(2);
	EXPECT_EQ(2, m.getSize());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 10;
	EXPECT_EQ(10, m[0][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(2);
	ASSERT_ANY_THROW(m[-1][0] = 10);
	ASSERT_ANY_THROW(m[0][-1] = 10);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(2);
	ASSERT_ANY_THROW(m[2][0] = 10);
	ASSERT_ANY_THROW(m[0][2] = 10);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(2);
	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrixes_of_equal_size)
{
	TDynamicMatrix<int> m(2),m1(2);
	ASSERT_NO_THROW(m = m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(2), m1(3);
	m[0][0] = 1;
	m1[2][2] = 2;
	int a = m.getSize();
	m = m1;
	int b = m.getSize();
	EXPECT_NE(a, b);
}

TEST(TDynamicMatrix, cant_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m(2), m1(3);
	ASSERT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(2), m1(2);
	m[0][0] = 10;
	m1 = m;
	EXPECT_TRUE(m == m1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 10;
	EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m(2), m1(3);
	EXPECT_FALSE(m == m1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(2), m1(2), m2(2);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			m[i][j] = 1;
			m1[i][j] = 2;
			m2[i][j] = 3;
		}
	}
	EXPECT_EQ(m2, m + m1);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(2), m1(3);
	ASSERT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(2), m1(2), m2(2);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			m[i][j] = 3;
			m1[i][j] = 2;
			m2[i][j] = 1;
		}
	}
	EXPECT_EQ(m2, m - m1);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m(2), m1(3);
	ASSERT_ANY_THROW(m - m1);
}

