#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
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
