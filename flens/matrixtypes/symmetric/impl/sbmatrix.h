/*
 *   Copyright (c) 2012, Michael Lehn, Klaus Pototzky
 *
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *   1) Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2) Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in
 *      the documentation and/or other materials provided with the
 *      distribution.
 *   3) Neither the name of the FLENS development group nor the names of
 *      its contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef FLENS_MATRIXTYPES_SYMMETRIC_IMPL_SBMATRIX_H
#define FLENS_MATRIXTYPES_SYMMETRIC_IMPL_SBMATRIX_H 1

#include <cxxblas/typedefs.h>
#include <flens/matrixtypes/symmetric/symmetricmatrix.h>
#include <flens/typedefs.h>

namespace flens {

// forward declarations

template <typename FS>
    class HbMatrix;

template <typename FS>
    class TbMatrix;

template <typename FS>
class SbMatrix
    : public SymmetricMatrix<SbMatrix<FS> >
{
    public:
        typedef FS                                  Engine;
        typedef typename Engine::ElementType        ElementType;
        typedef typename Engine::IndexType          IndexType;

        // view types from Engine
        typedef typename Engine::ConstView          EngineConstView;
        typedef typename Engine::View               EngineView;
        typedef typename Engine::NoView             EngineNoView;

        typedef typename Engine::ConstArrayView     ConstArrayView;
        typedef typename Engine::ArrayView          ArrayView;
        typedef typename Engine::Array              Array;

        // view types for
        typedef DenseVector<ConstArrayView>         ConstVectorView;
        typedef DenseVector<ArrayView>              VectorView;
        typedef DenseVector<Array>                  Vector;

        typedef HpMatrix<EngineConstView>           ConstHermitianView;
        typedef HpMatrix<EngineView>                HermitianView;
        typedef HpMatrix<EngineNoView>              HermitianNoView;

        typedef SbMatrix<EngineConstView>           ConstView;
        typedef SbMatrix<EngineView>                View;
        typedef SbMatrix<EngineNoView>              NoView;

        typedef TbMatrix<EngineConstView>           ConstTriangularView;
        typedef TbMatrix<EngineView>                TriangularView;
        typedef TbMatrix<EngineNoView>              TriangularNoView;

        SbMatrix();

        explicit
        SbMatrix(IndexType dim, StorageUpLo upLo, IndexType numOffDiags,
                 IndexType firstIndex = Engine::defaultIndexBase);

        SbMatrix(const Engine &engine, StorageUpLo upLo);

        SbMatrix(const SbMatrix &rhs);

        template <typename RHS>
            SbMatrix(const SbMatrix<RHS> &rhs);

        template <typename RHS>
            SbMatrix(SbMatrix<RHS> &rhs);

        template <typename RHS>
            SbMatrix(const Matrix<RHS> &rhs);

        // -- operators --------------------------------------------------------

        SbMatrix &
        operator=(const SbMatrix &rhs);

        template <typename RHS>
            SbMatrix &
            operator=(const Matrix<RHS> &rhs);

        template <typename RHS>
            SbMatrix &
            operator+=(const Matrix<RHS> &rhs);
 
        template <typename RHS>
            SbMatrix &
            operator-=(const Matrix<RHS> &rhs);
    
        SbMatrix<FS> &
        operator=(const ElementType &alpha);

        SbMatrix<FS> &
        operator+=(const ElementType &alpha);

        SbMatrix<FS> &
        operator-=(const ElementType &alpha);

        SbMatrix &
        operator*=(const ElementType &alpha);

        SbMatrix &
        operator/=(const ElementType &alpha);

        const ElementType &
        operator()(IndexType row, IndexType col) const;

        ElementType &
        operator()(IndexType row, IndexType col);





        // -- views ------------------------------------------------------------


        // hermitian views
        const ConstHermitianView
        hermitian() const;

        HermitianView
        hermitian();

        // symmetric views
        const ConstView
        symmetric() const;

        View
        symmetric();

        // triangular views
        const ConstTriangularView
        triangular() const;

        TriangularView
        triangular();

        VectorView
        viewDiag(IndexType diag = IndexType(0));

        const ConstVectorView
        viewDiag(IndexType diag = IndexType(0)) const;

        // -- methods ----------------------------------------------------------

        IndexType
        dim() const;

        IndexType
        numCols() const;

        IndexType
        numRows() const;

        IndexType
        firstIndex() const;

        IndexType
        lastIndex() const;
 
        IndexType
        numOffDiags() const;

        IndexType
        leadingDimension() const;

        StorageOrder
        order() const;

        const ElementType *
        data() const;

        ElementType *
        data();

        template <typename RHS>
            bool
            resize(const SbMatrix<RHS> &rhs,
                   const ElementType &value = ElementType());

        bool
        resize(IndexType dim, IndexType numOffDiags,
               IndexType firstIndex = Engine::defaultIndexBase,
               const ElementType &value = ElementType());

        // -- implementation ---------------------------------------------------

        const Engine &
        engine() const;

        Engine &
        engine();

        StorageUpLo
        upLo() const;

    private:
        Engine       _engine;
        StorageUpLo  _upLo;
};

} // namespace flens

#endif // FLENS_MATRIXTYPES_SYMMETRIC_IMPL_SBMATRIX_H
