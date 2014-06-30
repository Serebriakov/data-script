#include <cstring>
#include <vector>
#include <algorithm>

#include "datascript/scanner/tokens_storage.h"

struct _parser_token
{
	int sequence;
	int token_id;
	const char* begin;
	const char* end;
	struct _tokens_storage* owner;
};

struct compare_seq
{
	bool operator () (struct _parser_token* a, struct _parser_token* b)
	{
		return a->sequence < b->sequence;
	}
};

struct _tokens_storage
{
	int current_sequence;
	int last_sequence;
	std::vector <_parser_token*> tokens;
};
// ---------------------------------------------------------------------------
struct _tokens_storage* create_tokens_storage ()
{
	_tokens_storage* ts = new _tokens_storage;
	ts->current_sequence = 0;
	ts->last_sequence = 0;
	return ts;
}
// ---------------------------------------------------------------------------
void free_tokens_storage (struct _tokens_storage* ts)
{
	const std::size_t n = ts->tokens.size ();
	for (std::size_t i = 0; i < n; i++)
	{
		_parser_token* pt = ts->tokens[i];
		if (pt->end == 0 && pt->begin != 0)
		{
			delete[] pt->begin;
		}
		delete pt;
	}
	delete ts;
}
// ---------------------------------------------------------------------------
struct _parser_token* create_parser_token (struct _tokens_storage* ts, int token_id, const char* start, const char* end)
{
	struct _parser_token* pt = new _parser_token;
	pt->owner = ts;
	pt->sequence = ts->current_sequence++;
	pt->token_id = token_id;
	pt->begin = start;
	pt->end = end;
	ts->tokens.push_back (pt);
	return pt;
}
// ---------------------------------------------------------------------------
void free_parser_token (struct _parser_token* victim)
{
	if (!victim)
	{
		return;
	}
	std::vector <_parser_token*>& tokens = victim->owner->tokens;
	std::vector <_parser_token*>::iterator itr = std::lower_bound (tokens.begin (), tokens.end (), victim, compare_seq ());
	if (itr != tokens.end () && ((*itr)->sequence == victim->sequence))
	{
		tokens.erase (itr);
	}
	if (victim->end == 0 && victim->begin != 0)
	{
		delete[] victim->begin;
	}
	delete victim;
}
// ---------------------------------------------------------------------------
void persist_tokens (struct _tokens_storage* ts)
{
	_parser_token dummy;
	dummy.sequence = ts->last_sequence;
	std::vector <_parser_token*>& tokens = ts->tokens;
	std::vector <_parser_token*>::iterator itr = std::lower_bound (tokens.begin (), tokens.end (), &dummy, compare_seq ());
	for (; itr != tokens.end (); itr++)
	{
		_parser_token* pt = *itr;
		if (pt->begin && pt->end)
		{
			std::size_t len = pt->end - pt->begin;
			char* s = new char[len+1];
			std::memcpy (s, pt->begin, len);
			s[len] = 0;
			pt->begin = s;
			pt->end = 0;
		}
	}
	ts->last_sequence = ts->current_sequence;
}
// ---------------------------------------------------------------------------
int get_token_data (const struct _parser_token* tok, const char** begin, const char** end)
{
	*begin = tok->begin;
	*end = tok->end;
	return tok->token_id;
}