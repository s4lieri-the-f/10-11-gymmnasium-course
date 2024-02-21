#include <iostream>
#include <vector>
#include <algorithm>

typedef double elem_t;

class Matrix
{
private:
    elem_t **data;
    int row_count, col_count;
    int sigma(const std::vector<int> &alpha) const;

    // elem_t rec_det(elem_t & ans);
public:
    Matrix(const int m, const int n, const elem_t &def_val);
    Matrix(const int n, bool is_col, const elem_t &def_val);
    Matrix(const std::vector<elem_t> &v, bool is_col);
    Matrix(const std::vector<std::vector<elem_t>> &v);
    elem_t get_by_pos(int x, int y);
    void set_by_pos(int x, int y, const elem_t &val);
    std::pair<int, int> get_by_val(const elem_t &val);
    elem_t **return_data();
    std::pair<int, int> size();
    void set_all_zero();
    Matrix(const Matrix &M1);

    Matrix operator*(const Matrix &A) const;
    Matrix operator+(const Matrix &A) const;
    Matrix operator-(const Matrix &A) const;
    Matrix operator/(const Matrix &A) const;
    Matrix &operator=(const Matrix &right);
    elem_t det() const;
    Matrix inverse() const;
    friend void aux(const Matrix &A);
    friend std::ostream &operator<<(std::ostream &out, const Matrix &A);
    friend Matrix operator*(const Matrix &A, const int n);
    friend Matrix operator*(const int n, const Matrix &A);
    friend Matrix operator^(const Matrix &A, const int n);

    elem_t cofactor(int i, int j) const;

    ~Matrix()
    {
        for (int i = 0; i < row_count; i++)
        {
            delete[] data[i];
        }
        delete[] data;
    }
};

Matrix &Matrix::operator=(const Matrix &m)
{ // m1 = m2
    if (&m == this)
    {
        return *this;
    }
    else if ((row_count != m.row_count) || (col_count) != m.col_count)
    {
        std::cerr << "НЕТ.";
    }
    for (int x = 0; x < m.row_count; x++)
    {
        for (int y = 0; y < m.col_count; y++)
        {
            data[x][y] = m.data[x][y];
        }
    }
    return *this;
}

Matrix operator*(const Matrix &A, const int n)
{
    Matrix res(A.row_count, A.col_count, 0);
    for (int i = 0; i < A.row_count; i++)
        for (int j = 0; j < A.col_count; j++)
            A.data[i][j] *= n;
    return A;
}

Matrix operator*(const int n, const Matrix &A)
{
    Matrix res(A.row_count, A.col_count, 0);
    for (int i = 0; i < A.row_count; i++)
        for (int j = 0; j < A.col_count; j++)
            A.data[i][j] *= n;
    return A;
}

Matrix::Matrix(const Matrix &M1)
{
    row_count = M1.row_count;
    col_count = M1.col_count;
    data = (elem_t **)new elem_t *[row_count];

    for (int i = 0; i < row_count; i++)
        data[i] = (elem_t *)new elem_t[col_count];

    for (int i = 0; i < row_count; i++)
        for (int j = 0; j < col_count; j++)
            data[i][j] = M1.data[i][j];
}

std::ostream &operator<<(std::ostream &out, const Matrix &A)
{
    for (int i = 0; i < A.row_count; i++)
    {
        for (int j = 0; j < A.col_count; j++)
            out << A.data[i][j] << ' ';
        out << std::endl;
    }
    return out;
}

Matrix::Matrix(const int m, const int n, const elem_t &def_val = 0)
{
    elem_t **M = new elem_t *[m];
    for (int count = 0; count < m; count++)
    {
        M[count] = new elem_t[n];
    }
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            M[i][j] = def_val;
        }
    Matrix::data = M;
    row_count = m;
    col_count = n;
}

Matrix Matrix::operator+(const Matrix &A) const
{
    if (col_count != A.col_count && row_count != A.row_count)
    {
        std::cerr << "Bad dimensions" << std::endl;
        return A;
    }
    Matrix res(row_count, col_count);
    for (int i = 0; i < row_count; i++)
        for (int j = 0; j < col_count; j++)
            res.data[i][j] += data[i][j] + A.data[i][j];
    return res;
}

Matrix Matrix::operator-(const Matrix &A) const
{
    if (col_count != A.col_count && row_count != A.row_count)
    {
        std::cerr << "Bad dimensions" << std::endl;
        return A;
    }
    Matrix res(row_count, col_count);
    for (int i = 0; i < row_count; i++)
        for (int j = 0; j < col_count; j++)
            res.data[i][j] -= data[i][j] - A.data[i][j];
    return res;
}

Matrix Matrix::operator*(const Matrix &A) const
{
    if (col_count != A.row_count)
    {
        std::cerr << "Bad dimensions" << std::endl;
        return A;
    }
    Matrix res(row_count, A.col_count);
    for (int i = 0; i < res.row_count; i++)
        for (int j = 0; j < res.col_count; j++)
            for (int k = 0; k < col_count; k++)
                res.data[i][j] += data[i][k] * A.data[k][j];
    return res;
}

Matrix operator^(const Matrix &A, const int n)
{
    if (A.col_count != A.row_count)
    {
        std::cerr << "Bad dimensions" << std::endl;
        return A;
    }
    Matrix res(A.row_count, A.col_count);
    for (int i = 0; i < A.row_count; i++)
        for (int j = 0; j < A.col_count; j++)
            res.data[i][j] = A.data[i][j];
    for (int i = 0; i < n - 1; i++)
    {
        res = A * res;
    }
    return res;
}

Matrix::Matrix(const int n, bool is_col = true, const elem_t &def_val = 0)
{
    if (is_col) // проснись, чувак, это колонка
    {
        elem_t **M = new elem_t *[1];
        for (int count = 0; count < n; count++)
        {
            M[count] = new elem_t[n];
        }
        for (int i = 0; i < 1; i++)
            for (int j = 0; j < n; j++)
            {
                M[i][j] = def_val;
            }
        Matrix::data = M;
        row_count = 1;
        col_count = n;
    }
    else
    {
        elem_t **M = new elem_t *[n];
        for (int count = 0; count < n; count++)
        {
            M[count] = new elem_t[1];
        }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < 1; j++)
            {
                M[i][j] = def_val;
            }
        Matrix::data = M;
        row_count = n;
        col_count = 1;
    }
}

Matrix::Matrix(const std::vector<elem_t> &v, bool is_col)
{
    if (is_col) // проснись, чувак, это колонка
    {
        elem_t **M = new elem_t *[1];
        for (int count = 0; count < v.size(); count++)
        {
            M[count] = new elem_t[v.size()];
        }
        for (int i = 0; i < 1; i++)
            for (int j = 0; j < v.size(); j++)
            {
                M[i][j] = v[j];
            }
        Matrix::data = M;
        row_count = 1;
        col_count = v.size();
    }
    else
    {
        elem_t **M = new elem_t *[v.size()];
        for (int count = 0; count < v.size(); count++)
        {
            M[count] = new elem_t[1];
        }
        for (int i = 0; i < v.size(); i++)
            for (int j = 0; j < 1; j++)
            {
                M[i][j] = v[i];
            }
        Matrix::data = M;
        row_count = v.size();
        col_count = 1;
    }
}

Matrix::Matrix(const std::vector<std::vector<elem_t>> &v)
{
    int m = v.size();
    int n = v[0].size();
    elem_t **M = new elem_t *[m];
    for (int count = 0; count < m; count++)
    {
        M[count] = new elem_t[n];
    }
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            M[i][j] = v[i][j];
        }
    Matrix::data = M;
    row_count = m;
    col_count = n;
}

elem_t **Matrix::return_data()
{
    return data;
}

std::pair<int, int> Matrix::get_by_val(const elem_t &val)
{
    for (int i = 0; i < row_count; i++)
        for (int j = 0; j < col_count; j++)
        {
            if (data[i][j] == val)
            {
                auto res = std::make_pair(i + 1, j + 1);
                return res;
            }
        }
    auto res = std::make_pair(-1, -1);
    return res;
}

void Matrix::set_all_zero()
{
    for (int i = 0; i < row_count; i++)
        for (int j = 0; j < col_count; j++)
        {
            data[i][j] = 0;
        }
}

void Matrix::set_by_pos(int x, int y, const elem_t &val)
{
    if (x <= row_count && y <= col_count)
        data[x - 1][y - 1] = val;
    else
    {
        std::cerr << "Ne lez!";
        return;
    }
}

elem_t Matrix::get_by_pos(int x, int y)
{
    if (x <= row_count && y <= col_count)
        return data[x - 1][y - 1];
    else
    {
        std::cerr << "Ne trogay!";
        return -2e9;
    }
}

std::pair<int, int> Matrix::size()
{
    auto res = std::make_pair(row_count, col_count);
    return res;
}

elem_t Matrix::det() const
{
    if (row_count != col_count)
    {
        std::cerr << "Cannot calculate determinant for non-square matrix!";
        return 0;
    }

    if (row_count == 1)
    {
        return data[0][0];
    }

    elem_t determinant = 0;
    Matrix submatrix(row_count - 1, col_count - 1);

    for (int j = 0; j < col_count; j++)
    {
        for (int i = 1; i < row_count; i++)
        {
            int sub_i = 0;
            for (int k = 0; k < col_count; k++)
            {
                if (k != j)
                {
                    submatrix.data[sub_i][k] = data[i][k];
                    sub_i++;
                }
            }
        }

        determinant += (j % 2 == 0 ? 1 : -1) * data[0][j] * submatrix.det();
        std::cerr << determinant << std::endl;
    }

    return determinant;
}

int Matrix::sigma(const std::vector<int> &alpha) const
{
    int res = 0;
    for (int i = 0; i < alpha.size(); i++)
        for (int j = i + 1; j < alpha.size(); j++)
            if (alpha[i] > alpha[j])
                res++;
    return res % 2;
}

elem_t Matrix::cofactor(int i, int j) const
{
    elem_t res = (i + j) % 2 ? -1 : 1;
    Matrix wA(row_count - 1, row_count - 1);
    for (int x = 0; x < row_count; x++)
        for (int y = 0; y < row_count; y++)
        {
            // skip if i == j
            wA.data[i][j];
        }
    return res;
}

Matrix Matrix::inverse() const
{
    if (row_count != col_count)
    {
        std::cerr << "Matrix is not square." << std::endl;
        throw std::runtime_error("Matrix is not square");
    }

    elem_t determinant = det();
    if (determinant == 0)
    {
        std::cerr << "Matrix is not invertible." << std::endl;
        throw std::runtime_error("Matrix is not invertible");
    }

    Matrix adjoint(row_count, col_count);
    for (int i = 0; i < row_count; i++)
    {
        for (int j = 0; j < col_count; j++)
        {
            elem_t cofactor_val = cofactor(i, j);
            adjoint.set_by_pos(j + 1, i + 1, cofactor_val);
        }
    }

    Matrix inverse(row_count, col_count);
    for (int i = 0; i < row_count; i++)
    {
        for (int j = 0; j < col_count; j++)
        {
            elem_t adjoint_val = adjoint.get_by_pos(i + 1, j + 1);
            inverse.set_by_pos(i + 1, j + 1, adjoint_val / determinant);
        }
    }

    return inverse;
}

void aux(const Matrix &A)
{
    std::cout << "row_count: " << A.col_count << std::endl;
    std::cout << "col_count: " << A.row_count << std::endl;
}
