#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, empty_by_default)
{
	TStack<int> st(5);

	EXPECT_EQ(true, st.empty());
}

TEST(TStack, can_get_size)
{
	TStack<int> st(5);

	ASSERT_NO_THROW(st.Push(2));
	ASSERT_NO_THROW(st.Push(1));

	EXPECT_EQ(2, st.size());
}

TEST(TStack, can_get_full)
{
	TStack<int> st(3);

	ASSERT_NO_THROW(st.Push(2));
	ASSERT_NO_THROW(st.Push(1));

	EXPECT_EQ(false, st.full());

	ASSERT_NO_THROW(st.Push(3));

	EXPECT_EQ(true, st.full());
}

TEST(TStack, can_get_empty)
{
	TStack<int> st(3);

	ASSERT_NO_THROW(st.Push(2));
	ASSERT_NO_THROW(st.Pop());

	EXPECT_EQ(true, st.empty());

	ASSERT_NO_THROW(st.Push(3));

	EXPECT_EQ(false, st.empty());
}

TEST(TStack, can_push_elements)
{
	TStack<int> st(5);
	ASSERT_NO_THROW(st.Push(1));
}

TEST(TStack, can_pop_elements)
{
	TStack<int> st(5);

	ASSERT_NO_THROW(st.Push(2));
	ASSERT_NO_THROW(st.Push(1));

	int OutElement;
	ASSERT_NO_THROW(OutElement = st.Pop());
	EXPECT_EQ(1, OutElement);
}

TEST(TStack, can_view_top_element)
{
	TStack<int> st(5);

	ASSERT_NO_THROW(st.Push(2));
	ASSERT_NO_THROW(st.Push(1));

	int OutElement;
	ASSERT_NO_THROW(OutElement = st.TopElem());
	EXPECT_EQ(1, OutElement);
}

TEST(TStack, last_in_first_out)
{
	TStack<int> st(5);

	ASSERT_NO_THROW(st.Push(2));
	ASSERT_NO_THROW(st.Push(1));

	int OutElement1, OutElement2;

	ASSERT_NO_THROW(OutElement1 = st.Pop());
	ASSERT_NO_THROW(OutElement2 = st.Pop());

	EXPECT_EQ(1, OutElement1);
	EXPECT_EQ(2, OutElement2);
}

TEST(TStack, throws_when_popping_empty_stack)
{
	TStack<int> st(5);

	ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack, throws_when_viewing_top_element_in_empty_stack)
{
	TStack<int> st(5);

	ASSERT_ANY_THROW(st.TopElem());
}

TEST(TStack, throws_when_pushing_full_stack)
{
	TStack<int> st(1);

	ASSERT_NO_THROW(st.Push(1));

	ASSERT_ANY_THROW(st.Push(2));
}
