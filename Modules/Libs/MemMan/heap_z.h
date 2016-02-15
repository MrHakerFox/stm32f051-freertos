//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------

#ifndef __HEAP_Z_H
#define __HEAP_Z_H

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t BYTE;

#pragma pack( push, 1 )
//----------------------------------------------------------------------------
typedef union type_size {
	unsigned long mark;
	struct {
	unsigned long size:24;
	unsigned long type:8;
	};
}type_size;

// Memory Control Block (MCB)
//----------------------------------------------------------------------------
typedef struct heap_mcb
{
	struct heap_mcb *next;   	// ��������� �� ��������� MCB
			  					// mcb.next  ���������� MCM ������ ��������� ��
			  					// ������ MCB.
	struct heap_mcb *prev;   	// ��������� �� ���������� MCB.
								// ��� ������� MCB ���� ��������� ���������
								// ��� �� ����.
	union type_size ts;  		// ������ ����� ������ (� ������)

	void *owner;        		// �������� ����� ������ (TCB ���������)
								// ���������� �������������� ���� ������ ���������� ����� �� MCB
} heap_mcb;


//----------------------------------------------------------------------------
// ���������-��������� ���� (���-��������� t_heap)
//----------------------------------------------------------------------------
typedef struct heap_t
{ 	// ��������� �� ������ heap (������ MCB)
	struct heap_mcb *start;
	// ��������� �� ������ ��������� MCB
	struct heap_mcb *freem;
	// RAW ������ ����
	unsigned long hsize;
} heap_t;
#pragma pack( pop )

//----------------------------------------------------------------------------
// ��������� ����������� heap �� ���������� RAM �����������
extern heap_t system_heap;

// ������������� heap (������������ ��� �������) �� ���������� RAM �����������
void init_system_heap( int add_ram );

// ������������� ������������ ������ � �������� heap
void heapinit( heap_t *heap );

// ����������� ������ � ���� 'heap', �������� 'size' ����.
// ���������� ��������� �� ����������������� ������
// ���� � ���� �� ���������� ������, �� ���������� NULL
void *malloc_z( heap_t *heap, size_t size, int type, void *owner );

//----------------------------------------------------------------------------
// ����������� ����������������� ������, �� ������� ��������� 'ptr' � 'heap'.
// ���� ��������� ��������� �� ������, ������� �� ���� �������� �����
// malloc_z() ��� ��������� 'ptr' ����� 0, �� ������ �� ����������,
// �� �� ������� ����� �� exception :(
void free_z( heap_t *heap, void *ptr );


const char * getMemType( int type );


//----------------------------------------------------------------------------
enum MCB_MARK {
	MARK_FREE = 0,
	MARK_SYSTEM,
	MARK_TCB,
	MARK_STACK,
	MARK_QCB,
	MARK_QUEUE,
	MARK_CCB,
	MARK_MUTEX,
	MARK_CPP_NEW,
	MARK_CPP_NEW_ARR,
	MARK_A,
	MARK_B,
	MARK_C,
	MARK_D,
	MARK_E,
	MARK_F
};

//----------------------------------------------------------------------------
// ������ ������ ������
//----------------------------------------------------------------------------
void heaplist_z( heap_t *heap );

#ifdef __cplusplus
}
#endif

#endif /* __HEAP_Z_H */
